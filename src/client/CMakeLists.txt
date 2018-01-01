cmake_minimum_required (VERSION 3.0)

configure_file(client.py client.py) #Add client to the build directory
configure_file(test_client.py test_client.py)

add_test(NAME test_client COMMAND python3 test_client.py)
