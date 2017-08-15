
import os
import sys
import optparse
import re
import time

def GetOptions():
    parser = optparse.OptionParser()
    parser.add_option('-o', '--output',
                      dest="output",
                      help="output path for new files",
                      )
    parser.add_option('-l', '--list',
                      dest="list",
                      help="file list",
                      )
    options, remainder = parser.parse_args()
    return options

# do the replace
def replace(pattern, content):
    str_cnt = pattern.subn(r' ', content)
    while str_cnt[1] != 0:
        str_cnt = pattern.subn(r' ', str_cnt[0])

    return StrCnt[0]

def get_current_time():
    return time.strftime("[%Y-%m-%d %H:%M:%S]", time.localtime())

def main():
    options = GetOptions()

    with open(options.list, "r") as file_list_handler:

	    # all the match pattern
    	rplace_pattern = re.compile(r"""\/[0-9a-zA-Z.-_+/]+\/?      # path
        	                        |                               # other patterns
            		                """, re.X)

    	counter = 0
    	for file in file_list_handler:
        	file = file.rstrip('\n')
        	with open(file, "r") as file_handler:
        		counter = counter + 1
	
	        	os.system('mkdir -p ' + options.output)
	        	file_name = os.path.basename(file)
	        
	        	with open(options.output + '/' + file_name, 'w') as new_file_handler:
	
	        		print(get_current_time()),
	        		print("Generating new [%d] %s" % (counter ,file_name))
	
	        		content = file_handler.readlines()
	        	
	        	    new_content = replace(rplace_pattern, content)

        	        new_file_handler.write(new_content)
	


if __name__ == "__main__":
    sys.exit(main())
