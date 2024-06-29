#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#define FILE_NAME "DUY_MMAP"
#define SHARE_MEMORY_SIZE 100 // bytes
/*
    1. Tạo các file descriptor
    2. Set size
    3. Map/unmap cho share memory
    4. Xóa share memory map
*/

int main()
{
    int shm_fd = shm_open(FILE_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd < 0)
    {
        printf("Can't open share memory\n");
        exit(EXIT_FAILURE);
    }

    // set size for share memory
    ftruncate(shm_fd, SHARE_MEMORY_SIZE); // 100 bytes

    /**
     * void *mmap (void *addr, size_t length, int prot, int flags, int fd, off_t offset);
     * @brief Configure the size of the shared memory object.
     *
     * @param[in] addr địa chỉ memory của calling process được map. Tương tự như shm nên
     *                 set giá trị là 0 và kernel sẽ allocation addr phù hợp
     * @param[in] length độ dài của shared memory object được map (> 0).
     * @param[in] prot memory protection of mapping (không được conflict với file permission).
     *                 Có thể có các giá trị sau:
     *                 PROT_EXEC  ---> Pages may be executed.
     *                 PROT_READ  ---> Pages may be read.
     *                 PROT_WRITE ---> Pages may be written.
     *                 PROT_NONE  ---> Pages may not be accessed.
     * @param[in] flags cờ cho phép các process có thể thấy được cập nhật của các process vào
     *                  shared memory hay không.
     *                  MAP_SHARED  ---> cập nhật của process này vào shared memory là available với các process khác.
     *                  MAP_PRIVATE ---> kernel sử dụng phương thức copy-on-write để tạo ra vùng nhớ riêng cho thay
     *                              đổi của process. Các thay đổi này sẽ không visiable đối với các process khác.
     *                  Ngoài ra, ta có thể dùng phép OR để kết hợp với một số cờ sau:
     *                  MAP_ANONYMOUS ---> Tạo ra anonymous mapping. Toàn bộ ô nhớ trên vùng này được khởi tạo là 0.
     *                  Không cần quân tâm tới fd.
     *                  MAP_UNINITIALIZED ---> Không khởi tạo vùng anonymous mapping.
     *
     * @param[in] fd shm file descriptor
     * @param[in] offset offset của shared memory object sẽ được maping vào virtual memory của process.
     *
     * @return  On success, mmap() returns a pointer to the mapped area.
     *          On error, the value MAP_FAILED (that is, (void *) -1) is returned,
     *          and errno is set to indicate the cause of the error.
     */
    char *data = (char *)mmap(0, SHARE_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    // bởi vì ta sẽ được trả về là một pointer trỏ tới vùng đã được map. Từ đây có thể giúp chung ta thay đổi được giá trị của file.
    strcpy(data, "hello");
    printf("Data from share memory: %s in the file %s", data, __FILE__);
    munmap(&shm_fd, SHARE_MEMORY_SIZE);
    close(shm_fd);
}