import json
import subprocess
import difflib

def compareFiles(path1,path2):
    similar=True
    with open(path1) as file_1:
        file_1_text = file_1.readlines()
        # strip the newline character from the end of each line
        file_1_text = [line.rstrip() for line in file_1_text]
    
    with open(path2) as file_2:
        file_2_text = file_2.readlines()
        file_2_text = [line.rstrip() for line in file_2_text]

    
    # Find and print the diff:
    for line in difflib.unified_diff(
            file_1_text, file_2_text, fromfile='path1',
            tofile='path2', lineterm=''):
        print(line)
        similar=False

    return similar

if __name__ == '__main__':
    # Loop over tests cases in .json file
    # Open the JSON file
    with open('./test_cases.json') as f:
        # Load the JSON data
        data = json.load(f)
    
    failed_test_cases = []
    

    # Run C++ program for each test case
    for key, test_case in data.items():
        print("Running Test Case:", key)
        
        
        # Run the executable and pass input via stdin
        process = subprocess.Popen(["./main.exe"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

        # Read input string from file
        with open(test_case['input'], "r") as file:
          input_string = file.read()

        # Pass input string to the process
        output, errors = process.communicate(input=input_string)

        # Write output to file
        with open(test_case['output'], "w") as file:
          file.write(output)

        # Compare output with expected output
        similar = compareFiles(test_case['output'], test_case['output_gold'])

        if not similar:
            failed_test_cases.append(key)
    
    if len(failed_test_cases) == 0:
        print("All test cases passed!")
    else:
        print("Failed test cases:", failed_test_cases)
        print("Some test cases failed!")