# PROJECT CUSTOM TARGETS FILE
#  here you can define custom targets for the project so all team member can use it in the same way
#  some example of custo targets are shown bello those are targets for:
# 		1. Running unit tests
# 		2. Code Complexity Metrics
# 		3. CppCheck static analize of specific folder
# 		4. Code Coverage report generation.


#TARGETS FOR RUNNING UNIT TESTS
message(STATUS "To run Unit Tests, you can use predefine target: \r\n\trun,")
add_custom_target(run MENU_LIB_test)

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
						../../../src
						--CCN 12 -Tnloc=30 
						-a 4 
						--languages cpp 
						-V 
						-i 1)
# Create CCM report in reports/Cylcomatic_Complexity/
add_custom_command(
    OUTPUT ../../../reports/CCM/
    COMMAND ${CMAKE_COMMAND} -E make_directory ../../../reports/CCM/
    COMMENT "Tworzenie katalogów raportów Code Coverage"
)
add_custom_target(ccmr 
	COMMAND ${CMAKE_COMMAND} -E make_directory ../../../reports/CCM/
	COMMAND lizard 
				../../../src/ 
				--CCN 12 
				-Tnloc=30 
				-a 4 
				--languages cpp 
				-V 
				-o ../../../reports/CCM/lcd_menu_lib.html
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
add_custom_command(
    OUTPUT ../../../reports/CCR/ ../../../reports/CCR/JSON_ALL/
    COMMAND ${CMAKE_COMMAND} -E make_directory ../../../reports/CCR/
    COMMENT "Tworzenie katalogów raportów Code Coverage"
)
add_custom_target(ccr
	COMMAND ${CMAKE_COMMAND} -E make_directory ../../../reports/CCR/
	COMMAND gcovr 
				-r ../../../src/
				--html-details ../../../reports/CCR/lcd_menu_lib_report.html 
				.
)
		
add_custom_target(ccc gcovr  
						-r ../../../src
						--fail-under-line 90
						.
)

find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
	message(STATUS "clang-format was found, you can use predefined target for formating the code in project predefined standard : \r\n\tformat \r\n\tformat_test")
else()
	message(STATUS "clang-format was not found. \r\n\tInstall clang-format to get predefined target for formating the code in project predefined standard")
endif()
add_custom_target(format  clang-format 
							-i 
							-style=file 
							../../../src/*.c 
							../../../src/*.h
)
add_custom_target(format_test  clang-format 
								-i 
								-style=file 
								../*.c 
								../*.h
)