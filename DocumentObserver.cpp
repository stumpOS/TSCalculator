#include "DocumentObserver.h"
#include "Document.h"

DocumentObserver::DocumentObserver(Document *document):_document(document)
{
	_document->AddObserver(this);
}


DocumentObserver::~DocumentObserver(void)
{
	_document->RemoveObserver(this);
}