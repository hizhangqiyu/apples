
import os
import sys
import optparse
import re
import time

def GetOptions():
    parser = optparse.OptionParser()
    parser.add_option('-o', '--output',
                      dest="output",
                      help="output path for new logs",
                      )
    parser.add_option('-l', '--list',
                      dest="list",
                      help="the file contian logs list",
                      )
    options, remainder = parser.parse_args()
    return options

# do the replace
def Replace(pattern, string):
    StrCnt = pattern.subn(r' ', string)
    while StrCnt[1] != 0:
        StrCnt = pattern.subn(r' ', StrCnt[0])

    return StrCnt[0]

def GetCurrentTime():
    return time.strftime("[%Y-%m-%d %H:%M:%S]", time.localtime())

def main():
    options = GetOptions()

    hLogFileList  = open(options.list, "r")

    # all the match pattern
    replacePattern = re.compile(r"""\/[0-9a-zA-Z.-_+/]+\/?      # path
                                |                               # other pattern
                            """, re.X)

    counter = 0
    for logFile in hLogFileList:
        logFile = logFile.rstrip('\n')
        hLogFile = open(logFile, "r")
        counter = counter + 1

        os.system('mkdir -p ' + options.output)
        newLogFileName = os.path.basename(logFile)
        hNewLogFile = open(options.output + '/' + newLogFileName, 'w')

        print(GetCurrentTime()),
        print("Generating new [%d] %s" % (counter ,newLogFileName))

        allLines = hLogFile.readlines()
        for oneLine in allLines:
            newLine = Replace(replacePattern, oneLine)
            if not re.match(r'^\s+$', newLine):
                hNewLogFile.writelines(newLine)

        hLogFile.close()
        hNewLogFile.close()

    hLogFileList.close()


if __name__ == "__main__":
    sys.exit(main())
