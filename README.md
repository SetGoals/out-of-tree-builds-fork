# out-of-tree-builds

Welcome to my project! This project is about {{MY_VARIABLE}}.

import xml.etree.ElementTree as ET

def sanitize_xml(input_file, output_file):
    with open(input_file, 'r') as f:
        file_content = f.read()

    documents = file_content.split('<?xml version="1.0" encoding="UTF-8"?>')[1:]

    sanitized_results = ET.Element('results')
    current_errors = None
    encountered_nodes = set()

    for doc_content in documents:
        root = ET.fromstring(doc_content.strip())
        cppcheck = root.find('cppcheck')
        if cppcheck is not None and 'cppcheck' not in encountered_nodes:
            sanitized_results.append(cppcheck)
            encountered_nodes.add('cppcheck')
        
        errors = root.find('errors')
        if errors is not None:
            if current_errors is None:
                current_errors = ET.SubElement(sanitized_results, 'errors')
            for error in errors.findall('error'):
                error_text = error.text.strip()
                if error_text not in encountered_nodes:
                    new_error = ET.Element('error')
                    new_error.text = error_text
                    for child in error:
                        if child.tag == 'location':
                            new_location = ET.Element('location')
                            new_location.text = child.text
                            new_error.append(new_location)
                        else:
                            new_error.append(child)
                    current_errors.append(new_error)
                    encountered_nodes.add(error_text)

    sanitized_tree = ET.ElementTree(sanitized_results)
    sanitized_tree.write(output_file, xml_declaration=True, encoding='utf-8')

input_filename = '/Users/mattwalsh/Downloads/TestXMLsanitation/input_file.xml'
output_filename = '/Users/mattwalsh/Downloads/TestXMLsanitation/input_file.xml'

sanitize_xml(input_filename, output_filename)

