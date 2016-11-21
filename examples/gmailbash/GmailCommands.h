#pragma once

#include "GoogleClient.h"

using namespace googleQt;

namespace googleQt{
namespace messages
{
    class MessageResource;
};
namespace labels
{
    class LabelResource;
};    
}

class GmailCommands
{
public:
    GmailCommands(GoogleClient& c);

	/**
       ls - list messages
	*/
	void ls		(QString nextToken);

	/**
       ls_by_labels - list messages that belong to labels provided
	*/
	void ls_by_labels(QString labelIds);
    
	/**
       get - get message by id
	*/
	void get	(QString message_id);

	/**
		send - send new message, the body of the message should be stored
		in a text file
	*/
	void send(QString message_file_name);

	/**
		importMessage - import new message, the body of the message should be stored
		in a text file
	*/
	void importMessage(QString message_file_name);

	/**
		insertMessage - insert new message, the body of the message should be stored
		in a text file
	*/
	void insertMessage(QString message_file_name);

	/**
		trash - trash message by id
	*/
	void trash(QString message_id);

	/**
		untrash - untrash message by id
	*/
	void untrash(QString message_id);

	/**
		ls_labels - list labels
	*/
	void ls_labels(QString);

	/**
	get_label - get label
	*/
	void get_label(QString label_id);

	/**
	create_label - create label
	*/
	void create_label(QString name);

	/**
	delete_label - delete label
	*/
	void delete_label(QString label_id);

	/**
	update_label - update label
	*/
	void update_label(QString labelid_space_name);
    
	/**
	ls_threads - list threads
	*/
	void ls_threads(QString);

	/**
	get_thread - get thread info
	*/
	void get_thread(QString thread_id);

	/**
	ls_drafts - list drafts
	*/
	void ls_drafts(QString);

	/**
	get_draft - get draft info
	*/
	void get_draft(QString draft_id);

	/**
	history - get history
	*/
	void history(QString startHistoryIdStr);

protected:
    void listMessages(QString nextToken, QString labelIds);
	void listThreads(QString nextToken, QString labelIds);
	void listDrafts(QString nextToken);
    void printMessage(messages::MessageResource*);
    void printLabel(labels::LabelResource*);
	bool loadMessageFile(QString fileName, messages::MessageResource*);

protected:
    GoogleClient& m_c;
	GmailRoutes*  m_gm;
};
