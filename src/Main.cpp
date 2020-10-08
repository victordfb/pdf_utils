#include <iostream>
#include <cstring>
#include <podofo/podofo.h>
#include <memory>

using namespace PoDoFo;

using std::cin;
using std::cout;
using std::endl;
using std::string;

const std::size_t INIT_BUFFER_SIZE = 1024;

PdfMemDocument *nextPdf()
{
    try
    {
        // on some systems you may need to reopen stdin in binary mode
        // this is supposed to be reasonably portable
        std::freopen(nullptr, "rb", stdin);

        if (std::ferror(stdin))
            throw std::runtime_error(std::strerror(errno));

        std::size_t len;
        std::array<char, INIT_BUFFER_SIZE> buf;

        // somewhere to store the data
        std::vector<char> input;

        // use std::fread and remember to only use as many bytes as are returned
        // according to len
        while ((len = std::fread(buf.data(), sizeof(buf[0]), buf.size(), stdin)) > 0)
        {
            // whoopsie
            if (std::ferror(stdin) && !std::feof(stdin))
                throw std::runtime_error(std::strerror(errno));

            // use {buf.data(), buf.data() + len} here
            input.insert(input.end(), buf.data(), buf.data() + len); // append to vector
        }

        // use input vector here
    }
    catch (std::exception const &e)
    {
        std::cerr << e.what() << '\n';
        return nullptr;
    }
    return nullptr;
}

int main()
{
    int i;

    cout << "Carregando PDF..." << endl;

    try
    {
        PdfMemDocument *document = nextPdf();
        document->Write("../../teste_final.pdf");
        //PdfMemDocument document1;
        //PdfMemDocument document2;
        //document1.Load(file.c_str());
        //document2.Load(file.c_str());
        //document1.Append(document2);
        //document1.Write("../../teste_final.pdf");
    }
    catch (PdfError &e)
    {
        cout << e.what() << endl;
    }
}
