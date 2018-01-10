#
#/*****************************************************
#*                                                    *
#*  Copyright (c) 2016 Trevor Mellon                  *
#*  For further information contact t@jno.io          *
#*                                                    *
#*  Licensed under the BSD 3-clause license           *
#*  See LICENCE file for more information             *
#*                                                    *
#******************************************************/
#


# http://xit0.org/2013/04/cmake-use-git-branch-and-commit-details-in-project/
# Get the current working branch
execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest abbreviated commit hash of the working branch
execute_process(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
  COMMAND git rev-list HEAD --count
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_REV_COUNT
  OUTPUT_STRIP_TRAILING_WHITESPACE
)