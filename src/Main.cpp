#include <iostream>
#include <cstring>
#include <podofo/podofo.h>
#include <memory>
#include <vector>

using namespace PoDoFo;

using std::cin;
using std::cout;
using std::endl;
using std::string;

const std::size_t INIT_BUFFER_SIZE = 1024;
const string startMark = "%PDF";
const string eofMark = "%%EOF";
std::vector<char> *remaindr;

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
        if (remaindr)
        {
            input.insert(input.begin(), remaindr->begin(), remaindr->end());
        }

        // use std::fread and remember to only use as many bytes as are returned
        // according to len
        while ((len = std::fread(buf.data(), sizeof(buf[0]), buf.size(), stdin)) > 0)
        {
            // whoopsie
            if (std::ferror(stdin) && !std::feof(stdin))
                throw std::runtime_error(std::strerror(errno));

            char *pos = strstr(buf.data(), eofMark.c_str());
            if (pos)
            {
                // use {buf.data(), buf.data() + len} here
                input.insert(input.end(), buf.data(), pos + 5); // append to vector

                char *sPos = strstr(pos, startMark.c_str());
                if (sPos)
                {
                    delete remaindr;
                    remaindr = new std::vector<char>(sPos, buf.data() + len);
                }
                else
                {
                    delete remaindr;
                    remaindr = nullptr;
                }
                break;
            }
            else
            {
                // use {buf.data(), buf.data() + len} here
                input.insert(input.end(), buf.data(), buf.data() + len); // append to vector
            }
        }
        PdfMemDocument *document = new PdfMemDocument();
        document->LoadFromBuffer(reinterpret_cast<char *>(input.data()), input.size());
        return document;
    }
    catch (std::exception const &e)
    {
        std::cerr << e.what() << "--\n";
        return nullptr;
    }
}

int main()
{
    int i;

    cout << "Loading PDFs..." << endl;
    PdfMemDocument *document1 = nullptr;

    while (true)
    {
        try
        {
            PdfMemDocument *document = nextPdf();
            cout << "li + 1" << endl;
            if (!document1)
            {
                document1 = document;
            }
            else
            {
                document1->Append(*document);
                delete document;
            }
        }
        catch (PdfError &e)
        {
            std::cerr << e.what() << "--\n";
            break;
        }
    }
    if (document1)
    {
        cout << "Writing file" << endl;
        document1->Write("../../teste_final.pdf");
    }
}
