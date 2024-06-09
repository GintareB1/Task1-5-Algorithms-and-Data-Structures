#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void writeHTMLToFile() {
    int rows, columns, a = 1, width, x, n;
    string text, label;
    ofstream out("HTMLOutput.html");
    out << "<!DOCTYPE html>\n"
           "<html>\n"
           "<body>\n";
    while (a != 0) {
        cout << "What to add?\n"
             << "1. Table\n"
             << "2. Form\n"
             << "3. Navigation bar\n"
             << "4. Articles or sections\n"
             << "5. Heading\n"
             << "6. Plain text\n"
             << "0. Exit\n";
        cin >> a;
        switch (a) {
            case 1:
                cout << "How many rows?" << endl;
                cin >> rows;
                cout << "How many columns?" << endl;
                cin >> columns;
                out << "<style>\n"
                       "table, th, td {\n"
                       "  border:1px solid black;\n"
                       "}\n"
                       "</style>\n";
                cout << "What width (%)?" << endl;
                cin >> width;
                out << "<table style=width:" << width << "%>";
                cin.ignore();
                for (int i = 0; i < rows; ++i) {
                    out << "<tr>";
                    for (int j = 0; j < columns; ++j) {
                        cout << "What to write in " << i + 1 << " row and " << j + 1 << " column?" << endl;
                        getline(cin, text);
                        out << "<td>" << text << "</td>";
                    }
                    out << "</tr>";
                }
                out << "</table>";
                break;
            case 2:
                out << "<form>";
                cout << "What would you like to add?" << endl
                     << "1. Form\n"
                     << "2. Multiline Input field\n"
                     << "3. Radio Input or Checkbox Input\n";
                cin >> x;
                switch (x) {
                    case 1:
                        cout << "How many form fields?\n";
                        cin >> n;
                        cin.ignore();
                        for (int j = 0; j < n; ++j) {
                            cout << "Whats the label of " << j + 1 << " field?\n";
                            getline(cin, label);
                            out << "<label>" << label << "</label> <br>\n";
                            out << "<input type=\"text\"><br>\n";
                        }
                        break;
                    case 2:
                        cout << "How many rows and columns?\n";
                        cin >> rows >> columns;
                        out << " <textarea rows=\"" << rows << "\" cols=\"" << columns << "\"></textarea><br>\n";
                        break;
                    case 3:
                        cout << "Write radio or checkbox?\n";
                        cin.ignore();
                        getline(cin, text);
                        cout << "How many inputs?\n";
                        cin >> n;
                        cin.ignore();
                        for (int j = 0; j < n; ++j) {
                            cout << "Whats the label for " << j + 1 << " element?\n";
                            getline(cin, label);
                            out << "<input type=\"" << text << "\">\n<label>" << label << "</label><br>\n";
                        }
                        break;
                }
                break;
            case 3 :
                out << "<style>\n"
                       "ul {\n"
                       "  list-style-type: none;\n"
                       "  margin: 0;\n"
                       "  padding: 0;\n"
                       "  overflow: hidden;\n"
                       "  background-color: #333;\n"
                       "}\n"
                       "\n"
                       "li {\n"
                       "  float: left;\n"
                       "}\n"
                       "\n"
                       "li a {\n"
                       "  display: block;\n"
                       "  color: white;\n"
                       "  text-align: center;\n"
                       "  padding: 14px 16px;\n"
                       "  text-decoration: none;\n"
                       "}\n"
                       "\n"
                       "li a:hover {\n"
                       "  background-color: #111;\n"
                       "}\n"
                       "</style>\n<ul>";
                cout << "How many elements?\n";
                cin >> n;
                cin.ignore();
                for (int j = 0; j < n; ++j) {
                    cout << "What's the " << j + 1 << " element?\n";
                    getline(cin, text);
                    out << "<li><a href=\"#" << text << "\">" << text << "</a></li>\n";
                }
                out << "</ul>\n";
                break;
            case 4 :
                cout << "What's the header?\n";
                cin.ignore();
                getline(cin, text);
                out << "<h2>" << text << "</h2>";
                cout << "Whats the section text?\n";
                getline(cin, text);
                out << "<section>" << text << "</section>\n";
                break;
            case 5 :
                cout << "What heading?\n";
                cin.ignore();
                getline(cin, text);
                out << "<h1>" << text << "</h1>\n";
                break;
            case 6 :
                cout << "What text?";
                cin.ignore();
                getline(cin, text);
                out << "<p>" << text << "</p>\n";
                break;
            case 0:
                break;
            default:
                cout << "Invalid option. Please try again.\n";
                break;
        }
    }
    out << "</body>\n"
           "</html>";
    out.close();
}

int main() {
    writeHTMLToFile();
    cout << "HTML file has been created successfully." << endl;
    return 0;
}
