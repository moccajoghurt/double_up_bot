#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

using namespace std;

int main()
{
    char *outText;
    
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    
    /*api->SetVariable("tessedit_char_whitelist", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    api->SetVariable("language_model_penalty_non_freq_dict_word", "0");
    api->SetVariable("language_model_penalty_non_dict_word", "0");
    api->SetVariable("tessedit_char_blacklist", "riaxyz");
    api->SetVariable("classify_bln_numeric_mode", "1");*/
    
    //api->SetVariable("tessedit_char_blacklist", "maria]");
    //api->SetVariable("load_system_dawg", "F");
    //api->SetVariable("load_freq_dawg", "F");
    
    // Initialize tesseract-ocr with English
    if (api->Init("res/tessdata", "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }
    
    //api->SetVariable("tessedit_char_blacklist", "maria]");
    //api->SetVariable("language_model_penalty_non_dict_word", "0");
    //api->SetVariable("language_model_penalty_non_freq_dict_word", "0");
    api->SetVariable("tessedit_char_whitelist", "0123456789,");
    
    // Open input image with leptonica library
    Pix *image = pixRead("number.bmp");
    api->SetImage(image);
    // Get OCR result
    outText = api->GetUTF8Text();
    printf("OCR output:\n%s", outText);

    // Destroy used object and release memory
    api->End();
    //delete [] outText;
    pixDestroy(&image);

    return 0;
}
