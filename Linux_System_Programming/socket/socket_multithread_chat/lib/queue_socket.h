struct node
{
    struct node *next; // using type node for next for pointing to client_socket which is data of node
    int *client_socket;
};
typedef struct node node_t;

node_t *head = NULL;
node_t *tail = NULL;
/*
    Enqueue is adding client_socket into queue, this queue first create new_node by malloc for preventing memory overlap
    then initialize this new node by assign NULL for next pointer and data for client_socket

*/
void enqueue(int *client_socket)
{
    node_t *new_node = malloc(sizeof(node_t));
    new_node->next = NULL;
    new_node->client_socket = client_socket;
    if (tail == NULL)
    {
        head = new_node; // at first node, it is also head and tail
    }
    else
    {
        tail->next = new_node; // if there was a node in the queue then tail is also the last node, so tail->next = new_node
    }
    tail = new_node; // tail always the node has been added
}
int *dequeue()
{
    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        int *data = head->client_socket;
        node_t *temp = head; // hold node for head
        head = head->next;   // head is next node
        if (head == NULL)    // check if there is no node in queue, prevent tail pointer point something doesn't exist
        {
            tail = NULL;
        }
        free(temp); // drop node
        return data;
    }
}
