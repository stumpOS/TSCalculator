#pragma once
#ifndef DOCUMENTOBSERVER_H_
#define DOCUMENTOBSERVER_H_
class Document;
class DocumentObserver
{
public:
	~DocumentObserver(void);
	virtual void Observe() = 0;
	Document *GetDocument(){return _document;}

protected:
	DocumentObserver(Document *d);
private:
	DocumentObserver();
	Document *_document;
};
#endif

