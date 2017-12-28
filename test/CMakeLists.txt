cmake_minimum_required (VERSION 3.0)
configure_file(client_unit.py client_unit.py)

# Add Python test. Ensure PYTHONPATH is set to the binary directory where the client.py file is located. We set the PYTHONPATH in the src directory
#set(ENV{PYTHONPATH} ${CMAKE_BINARY_DIR}/src)
add_test(NAME client_test COMMAND bash -c "export PYTHONPATH=${PYTHONPATH} && python3 client_unit.py")

