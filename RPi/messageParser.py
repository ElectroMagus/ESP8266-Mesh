filename = "parsedLogServer.messages"

node_id = set()


file = open(filename, "r")
for line in file:
    rawMsg = line.split(' ')
    sensorMsg = rawMsg[6:8]
    if sensorMsg[0] not in node_id: 
        node_id.add(sensorMsg[0])
    
print len(node_id)