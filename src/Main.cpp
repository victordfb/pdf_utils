#include <iostream>
#include <string>
#include <podofo/podofo.h>

using namespace PoDoFo;

using std::cout;
using std::endl;
using std::string;

int main()
{
    string file = "../../teste.pdf";
    cout << "Carregando PDF..." << endl;
    try
    {
        PdfMemDocument document;
        document.Load(file.c_str());
    }
    catch (PdfError &e)
    {
        cout << e.what() << endl;
    }
}
