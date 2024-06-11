require 'socket'
#write autotamic by ruby must tab after using require and using begin end for more clearly
begin
  start_time = Process.clock_gettime(Process::CLOCK_MONOTONIC)

  #create a socket client with ip & port 127.0.0.1,8989
  s = TCPSocket.new('localhost', 8983)
  s.write("/text/#{ARGV[0]}.c") #send a message to server

  s.each_line do |line| 
    # Uncomment the next line if you want to print each line received from the server, to read file 
    # puts line 
  end 

  s.close #close a socket client

  end_time = Process.clock_gettime(Process::CLOCK_MONOTONIC) #calculate time after excuted
  elapsed = end_time - start_time
  puts "Elapsed: #{elapsed} (#{ARGV[0]}) \n" #time to read files, and which file being read

#Error handling
rescue Errno::ECONNREFUSED => e
  puts "Connection refused. Ensure the server is running and reachable."
  puts e.message
rescue StandardError => e
  puts "An error occurred: #{e.message}"
end
