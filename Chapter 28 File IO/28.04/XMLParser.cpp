//
// Created by Cory Brown on 16/07/2017.
//

typedef unsigned long int ULI;

// TODO:
// if a comment is read then skip current line e.g. if second character isn't alpha-numeric

#include "XMLParser.h"

namespace Parser {
		XMLParser::XMLParser(const string& fileName) {
			ifstream open_file;
			open_file.open(fileName);

			ULI checkXML = fileName.find('.'); // check
			string getExtension = fileName.substr(checkXML);

			for (int i = 0; i < getExtension.size(); i++)
				tolower(getExtension[i]);

			if (checkXML == string::npos || getExtension != ".xml") {
				cout << "You need to pass a XML file" << endl;
				exit(1);
			}

			if (!open_file.is_open()) {
				cout << "Error opening file" << endl;
				exit(1);
			}
			while (!open_file.eof()) {
				this->nodeStart(open_file);
				if (!this->nodeTextRead(open_file)) {
					continue;
				}
			}
			open_file.close();
		}

		void XMLParser::nodeStart(ifstream& tag) {
			string node;
			getline(tag, node, '>'); // get the full node (including attribute, if present)
			if (node.front() == '<') {
				node.erase(node.begin());
			} // removes first angle bracket

			if (node.front() == '/') {
				return this->nodeEnd(node);
			} // check if its a closing node


			ULI space_location = node.find(' '); // finds space before the attribute

			if(space_location != string::npos) { // checks if space is present in string (if the node has an attribute)
				string attribute = node.substr(space_location); // gets a substring of the attribute
				attribute.erase(0,1); // removes white space at the beginning
				node.erase(space_location); // removes the attribute form the node string
				cout << "Opening Tag: " << node << endl;
				this->attributeRead(attribute);
			} else {
				cout << "Opening Tag: " << node << endl;
			}
		}

		void XMLParser::attributeRead(string& attribute) {
			ULI attribute_length = attribute.find('='); // length of attribute string
			string attribute_name = attribute.substr(0, attribute_length); // name of attribute
			string attribute_val = attribute.substr(attribute_length); //  value of attribute
			attribute_val.erase(0,1);
			cout << "Attribute: " << attribute_name << "=" << attribute_val << endl;
		}

		bool XMLParser::nodeTextRead(ifstream& textNode) {
			string text;
			getline(textNode, text, '<'); // reading line up-to a node
			if (text.empty() || text.find_first_not_of("\t\n ") == string::npos) { // checking if the string is empty or contains whitespace, tabs or newlines
				return false;
			}
			cout << "Text node: " << text << endl;
			return true;
		}

		void XMLParser::nodeEnd(string& endNode) {
			cout << "Ending Node: " << endNode << endl;
		}

}
