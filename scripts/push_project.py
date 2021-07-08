#usr/bin/python3

# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
# 
#  http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.

# Import libaries
import os
import sys
import subprocess

# Define constants
include_folder = "include/"
header_file = "version.hpp"
file_path = include_folder + header_file

'''
Get the last build version
@param file the file to check
@return build version
'''
def get_buildver(filename) :
	# Open the file
	file = open(filename, "r")

	# Build version
	buildver = 0

	# Get file content
	content = file.readlines()
 
	# Strips the newline character
	for line in content :
		line = line.split(" ")

		# Get the build version from the file
		if "BUILDVER"in line :
			buildver =  int(line[2])
			break

	# Close the file after the successful operation
	file.close()

	# Return 1 if there is no such line
	return buildver

'''
Get user's message to the commit
@return the message
'''
def get_msg() : 
	msg = input("[push_project.py] Write a commit message (press ENTER to use just build number) : ")
	return msg

'''
Clear branch name from different leading characters
@param name the name of the branch to process
@return the cleared name
'''
def clear_branch(name):
	return name.replace("* ", "").strip()

'''
Get the name of the branch to push 
@return name of the branch and a flag to indicate if the 
	branch is new
'''
def get_branch():
	# Get the list of branches
	branches = subprocess.check_output(
		"git branch", 
		shell=True).decode(sys.stdout.encoding).split("\n")
	for branch in branches:
		branch = clear_branch(branch)

	# Get current branch
	current_branch = clear_branch(
			subprocess.check_output(
				"git branch --show-current", 
				shell=True).decode(sys.stdout.encoding))
	print("[push_project.py] Current branch : ", current_branch)
	
	# Get user's input
	checkout_branch = input("[push_project.py] Enter the branch to commit to (to use current branch press ENTER) : ")
	if not checkout_branch:
		return [current_branch, False]

	return [checkout_branch, branch in branches]

def upload() :
	# Change the branch if needed
	[branch, is_new] = get_branch()
	if branch:
		if is_new :
			os.system("git checkout -b {0}".format(branch))
		else :
			os.system("git checkout {0}".format(branch))

	# Add local changes to the commit
	os.system("git add -A")

	# Commit the changes with user's message
	msg = get_msg()
	buildver = get_buildver(file_path)
	if not msg :
		os.system("git commit -m \"Build {0}\"".format(buildver))
	else:
		os.system("git commit -m \"Build {0} : {1}\"".format(buildver, msg))

	# Push the changes to the repo
	os.system("git push origin {0}".format(branch))

'''
The main function
'''
def main() :
	upload()

if __name__ == "__main__" :
	main()