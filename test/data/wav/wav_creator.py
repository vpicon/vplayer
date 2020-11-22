#! /usr/bin/python3


def labelToArray(label):
    byte_arr = []
    for i in range(4):
        byte_arr.append(ord(label[i]))

    return byte_arr



def intToLittleEndian(x, size):
    byte_arr = []
    for i in range(size // 8):
        byte_arr.append(x % 256)
        x = x // 256

    return byte_arr



def RIFFChunk():
    byte_arr = []

    byte_arr += labelToArray("RIFF")     \
              + intToLittleEndian(3, 32) \
              + labelToArray("WAVE") 

    return byte_arr


def formatChunk(frameRate, bitDepth, numChannels):
    formatCode = 1 # Wave Format PCM
    byteRate  = frameRate * numChannels * bitDepth // 8
    blockSize = numChannels * bitDepth // 8

    byte_arr = []

    byte_arr += labelToArray("fmt ")               \
              + intToLittleEndian(16,          32) \
              + intToLittleEndian(formatCode,  16) \
              + intToLittleEndian(numChannels, 16) \
              + intToLittleEndian(frameRate,   32) \
              + intToLittleEndian(byteRate,    32) \
              + intToLittleEndian(blockSize,   16) \
              + intToLittleEndian(bitDepth,    16) \

    return byte_arr



def dataChunk(data_arr):
    data_size = len(data_arr)

    byte_arr = []

    byte_arr += labelToArray("data")             \
              + intToLittleEndian(data_size, 32) \
              + data_arr

    return byte_arr
    


# Creates a wav file named filename, of 44.1 kHz sample rate,
# signed int 32 bits PCM data, stereo; containing data samples
# from data_arr
def createWAV(filename, data_arr):
    # Open file as write binary mode
    f = open(filename, "w+b")

    # Create wav binary data
    byte_arr  = RIFFChunk() + formatChunk(44100, 32, 2) + dataChunk(data_arr)

    binary_format = bytearray(byte_arr)

    # Write to file
    f.write(binary_format)

    # Close file
    f.close()



if __name__ == "__main__":
    # filename of the target wav file
    filename = "testShort.wav"

    # Define binary data to write
    data_arr = [00, 251, 12, 131, 31, 12, 13, 200]

    createWAV(filename, data_arr)
