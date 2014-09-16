passiveMockDataFile = 'files/passive_mock.txt' 
lineLength = 256
charRange = 256

print 'Generating mock data to files: '
print passiveMockDataFile

mockFile = open(passiveMockDataFile, "w")

# Generates 'lineLength' characters per line with values between 0 and 'charRange'
# will do that from 0 to charRange and then from charRange to 0
for char in range(0, charRange):
	for pos in range(0, lineLength):
		mockFile.write(chr(char))
	mockFile.write('\n')

for char in reversed(range(0, charRange)):
	for pos in range(0, lineLength):
		mockFile.write(chr(char))
	mockFile.write('\n')

mockFile.close()