filename = "parsedLogServer.messages"
node_id = set()

def main():
    file = open(filename, "r")
    for line in file:
        rawMsg = line.split(' ')                # Whitespace separation for now 
        sensorMsg = rawMsg[6:8]                 # The goodies are in columns 7 and 8
        if sensorMsg[0] not in node_id:     # A set evaluation function - Python rocks...  
            node_id.add(sensorMsg[0])       # Adds items to the set if they arn't there already
        sendMQTT(sensorMsg[1])                  # Pass off the already formatted message to a handler
    print len(node_id)                          # Num of unique Sensor ID's



def sendMQTT(msg):
    print msg
    
main()