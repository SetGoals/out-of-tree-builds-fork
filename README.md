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
                error_attrib = tuple(error.attrib.items())
                if error_attrib not in encountered_nodes:
                    new_error = ET.Element('error', **error.attrib)
                    new_error.text = error.text.strip()
                    for child in error:
                        if child.tag == 'location':
                            new_location = ET.Element('location', **child.attrib)
                            new_location.text = child.text.strip()
                            new_error.append(new_location)
                        else:
                            new_child = ET.Element(child.tag, **child.attrib)
                            new_child.text = child.text.strip()
                            new_error.append(new_child)
                    current_errors.append(new_error)
                    encountered_nodes.add(error_attrib)

    sanitized_tree = ET.ElementTree(sanitized_results)
    sanitized_tree.write(output_file, xml_declaration=True, encoding='utf-8')

sanitize_xml(input_filename, output_filename)

