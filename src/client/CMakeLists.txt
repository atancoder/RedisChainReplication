cmake_minimum_required (VERSION 3.0)

configure_file(client.py client.py) #Add client to the build directory
configure_file(client_unit.py client_unit.py)

add_test(NAME client_test COMMAND python3 client_unit.py)
