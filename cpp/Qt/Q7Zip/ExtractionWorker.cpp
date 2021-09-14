#include "ExtractionWorker.h"

#include "Q7Zip.h"


ExtractionWorker::ExtractionWorker()
    : q7zip_(nullptr)
{
}


ExtractionWorker::~ExtractionWorker()
{
}


void ExtractionWorker::extract()
{
    if (q7zip_ == nullptr)
        q7zip_ = new Q7Zip(this);


}
