# PROJECT CUSTOM TARGETS FILE
#  here you can define custom targets for the project so all team member can use it in the same way
#  some example of custo targets are shown bello those are targets for:
# 		1. Running unit tests
# 		2. Code Complexity Metrics
# 		3. CppCheck static analize of specific folder
# 		4. Code Coverage report generation.


#TARGETS FOR RUNNING UNIT TESTS
message(STATUS "To run Unit Tests, you can use predefine target: \r\n\trun,")
add_custom_target(run template_test)

# TARGET FOR CHECKING CODE COMPLEXITY METRICS"
# check if lizard software is available 
find_program(lizard_program lizard)
if(lizard_program)
	message(STATUS "Lizard was found, you can use predefined targets for src folder Code Complexity Metrics: \r\n\tccm,\r\n\tccmr,")
else()
	message(STATUS "Lizard was not found. \r\n\tInstall Lizard to get predefined targets for src folder Code Complexity Metrics")
endif()
# Prints CCM for src folder in the console
add_custom_target(ccm lizard 
						../../../src/ 
						--CCN 12 -Tnloc=30 
						-a 4 
						--languages cpp 
						-V 
						-i 1)
# Create CCM report in reports/Cylcomatic_Complexity/
add_custom_target(ccmr lizard 
						../../../src/ 
						--CCN 12 
						-Tnloc=30 
						-a 4 
						--languages cpp 
						-V 
						-o ../../../reports/CCM/template.html)

# TARGET FOR MAKING STATIC ANALYSIS OF THE SOURCE CODE AND UNIT TEST CODE
# check if cppchec software is available 
find_program(cppcheck_program cppcheck)
if(cppcheck_program)
	message(STATUS "CppCheck was found, you can use predefined targets for static analize : \r\n\tcppcheck,")
else()
	message(STATUS "CppCheck was not found. \r\n\tInstall CppCheck to get predefined targets for static analize")
endif()
add_custom_target(cppcheck cppcheck
					../../../src/template
					../../../test/template
					-i../../../test/template/out
					--enable=all
					--force
					# --inconclusive
					--std=c99
					# --inline-suppr 
					# --platform=win64 
					--suppress=missingIncludeSystem 
					--suppress=missingInclude
					# --suppress=unusedFunction:../../../test/template/template_test_runner.c:3
					# --checkers-report=cppcheck_checkers_report.txt
					)
# TARGET FOR CREATING CODE COVERAGE REPORTS
# check if python 3 and gcovr are available 
find_program(GCOVR gcovr)
find_program(PYTHON python)
if(PYTHON)
	if(GCOVR)
		message(STATUS "python 3 and gcovr was found, you can use predefined targets for uint tests code coverage report generation : \r\n\tccc, \r\n\tccr")
	else()
		message(STATUS "pyton 3 was found but gcovr was not found. \r\n\tInstall gcovr to get predefined targets for uint tests code coverage report generation")
	endif()
else()
	if(GCOVR)
		message(STATUS "python3 was not found. \r\n\tInstall python 3 to get predefined targets for uint tests code coverage report generation")
	else()
		message(STATUS "python3 and gcovr were not found. \r\n\tInstall python 3 and gcovr to get predefined targets for uint tests code coverage report generation")
	endif()
endif()
add_custom_target(ccr python -m gcovr 
						-r ../../../lib/template 
						--json ../../../reports/CCR/JSON_ALL/coverage_template.json
						--json-base  src/template
						--html-details ../../../reports/CCR/template/template_report.html 
						.)
add_custom_target(ccc python -m gcovr  
						-r ../../../lib/template 
						--fail-under-line 90
						.)

add_custom_target(ccca python -m gcovr  
						-r ../../../ 
						--json-add-tracefile ../../../reports/CCR/JSON_ALL/coverage_*.json  
						.)
						
add_custom_target(ccar python -m gcovr  
						-r ../../../ 
						--json-add-tracefile ../../../reports/CCR/JSON_ALL/coverage_*.json  
						--html-details -o ../../../reports/CCR/HTML_OUT/project_coverage.html
						.)
add_dependencies(ccra ccr)
add_dependencies(ccca ccr)

find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
	message(STATUS "clang-format was found, you can use predefined target for formating the code in project predefined standard : \r\n\tformat \r\n\tformat_test")
else()
	message(STATUS "clang-format was not found. \r\n\tInstall clang-format to get predefined target for formating the code in project predefined standard")
endif()
add_custom_target(format  clang-format -i -style=file 
				../../../src/template/*.c 
				../../../src/template/*.h)
add_custom_target(format_test  clang-format -i -style=file 
				../*.c 
				../*.h)