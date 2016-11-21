#pragma once

#include "google/endpoint/ApiUtil.h"

namespace googleQt{
    namespace gmail{
        DECLARE_PATH_CLASS(modify);
        DECLARE_PATH_CLASS(send);
        DECLARE_PATH_CLASS(trash);
        DECLARE_PATH_CLASS(untrash);
        DECLARE_PATH_CLASS(import);
		DECLARE_PATH_CLASS(insert);
        DECLARE_PATH_CLASS(batchDelete);

        class ListArg: public QParamArg
        {
        public:
            ListArg();
            
            /**
             * Include messages from SPAM and TRASH in the results. (Default: false)
             */
            bool          getIncludeSpamTrash()const{return m_includeSpamTrash;};
            void          setIncludeSpamTrash(bool v){m_includeSpamTrash = v;}

            /**
             * 	Only return messages with labels that match all of the specified label IDs.
             */
            QStringList&  labels(){return m_labelIds;}

            /**
             *  Maximum number of messages to return.
             */
            int           getMaxResults()const{return m_maxResults;};
            void          setMaxResults(int val){m_maxResults = val;}

            /**
             * Page token to retrieve a specific page of results in the list.
             */
            QString       getPageToken()const{return m_pageToken;}
            void          setPageToken(QString v){m_pageToken = v;}

            /**
             * Only return messages matching the specified query. Supports the same query format as the Gmail search box. 
             * For example, "from:someuser@example.com rfc822msgid: is:unread".
             */
            QString       getQ()const{return m_q;}
            void          setQ(QString v){m_q = v;}

			void build(const QString& link_path, QUrl& url)const override;
            
#ifdef API_QT_AUTOTEST
			static std::unique_ptr<ListArg> EXAMPLE();
#endif //API_QT_AUTOTEST


        protected:
            bool        m_includeSpamTrash;
            QStringList m_labelIds;
            int         m_maxResults;
            QString     m_pageToken;
            QString     m_q;
        };
        
		class HistoryListArg : public QParamArg
		{
		public:
			HistoryListArg(int startHistoryId);

			/**
			* 	Only return messages with labels that match all of the specified label IDs.
			*/
			QStringList&  labels() { return m_labelIds; }

			/**
			*  The maximum number of history records to return. 
			*/
			int           getMaxResults()const { return m_maxResults; };
			void          setMaxResults(int val) { m_maxResults = val; }

			/**
			* Page token to retrieve a specific page of results in the list.
			*/
			QString       getPageToken()const { return m_pageToken; }
			void          setPageToken(QString v) { m_pageToken = v; }

			/**
			* Required. Returns history records after the specified startHistoryId. 
			* The supplied startHistoryId should be obtained from the historyId of a message, 
			* thread, or previous list response. History IDs increase chronologically but are not 
			* contiguous with random gaps in between valid IDs. Supplying an invalid or out of date 
			* startHistoryId typically returns an HTTP 404 error code. A historyId is typically valid 
			* for at least a week, but in some rare circumstances may be valid for only a few hours. 
			* If you receive an HTTP 404 error response, your application should perform a full sync. 
			* If you receive no nextPageToken in the response, there are no updates to retrieve and you 
			* can store the returned historyId for a future request. 
			*/
			int           getStartHistoryId()const { return m_startHistoryId; }
			void          setStartHistoryId(int v) { m_startHistoryId = v; }

			void build(const QString& link_path, QUrl& url)const override;
#ifdef API_QT_AUTOTEST
			static std::unique_ptr<HistoryListArg> EXAMPLE();
#endif //API_QT_AUTOTEST

		protected:
			QStringList m_labelIds;
			int         m_maxResults;
			QString     m_pageToken;
			uint16_t    m_startHistoryId;
		};
		
		class DraftListArg : public QParamArg 
		{
		public:
			DraftListArg();

			/**
			* Include messages from SPAM and TRASH in the results. (Default: false)
			*/
			bool          getIncludeSpamTrash()const { return m_includeSpamTrash; };
			void          setIncludeSpamTrash(bool v) { m_includeSpamTrash = v; }

			/**
			*  The maximum number of history records to return.
			*/
			int           getMaxResults()const { return m_maxResults; };
			void          setMaxResults(int val) { m_maxResults = val; }

			/**
			* Page token to retrieve a specific page of results in the list.
			*/
			QString       getPageToken()const { return m_pageToken; }
			void          setPageToken(QString v) { m_pageToken = v; }

			/**
			* Only return messages matching the specified query. Supports the same query format as the Gmail search box.
			* For example, "from:someuser@example.com rfc822msgid: is:unread".
			*/
			QString       getQ()const { return m_q; }
			void          setQ(QString v) { m_q = v; }

			void build(const QString& link_path, QUrl& url)const override;

#ifdef API_QT_AUTOTEST
			static std::unique_ptr<DraftListArg> EXAMPLE();
#endif //API_QT_AUTOTEST

		protected:
			bool        m_includeSpamTrash;
			int         m_maxResults;
			QString     m_pageToken;
			QString     m_q;
		};


        class IdArg : public QParamArg
        {
        public:
			IdArg(){};
			IdArg(QString idValue);
            //virtual QString arg()const;
			void build(const QString& link_path, QUrl& url)const override;

			QString getId()const { return m_id; }
			void    setId(QString id) { m_id = id; };

            QString      getFormat()const{return m_format;}
            void         setFormat(QString f){m_format = f;}
            QStringList& headers(){return m_headers;}

#ifdef API_QT_AUTOTEST
			static std::unique_ptr<IdArg> EXAMPLE();
#endif //API_QT_AUTOTEST

        protected:
			QString     m_id;
            QString     m_format;
            QStringList m_headers;
        };       

        class ModifyMessageArg: public PathWithIdArg<path_modify, ModifyMessageArg>
        {
        public:
            ModifyMessageArg(QString idValue){m_id = idValue;}
        };
    
        class SendMessageArg: public PathArg<path_send, SendMessageArg>
        {
        public:
			SendMessageArg();
			void build(const QString& link_path, QUrl& url)const override;

			/**
			The type of upload request to the /upload URI. Acceptable values are: 
			media - Simple upload. Upload the media only, without any metadata.
			multipart - Multipart upload. Upload both the media and its metadata, in a single request.
			resumable - Resumable upload. Upload the file in a resumable fashion, using a series of 
			at least two requests where the first request includes the metadata.
			*/
			QString getUploadType()const { return m_uploadType; }
			void    setUploadType(QString val) { m_uploadType = val; }

#ifdef API_QT_AUTOTEST
			static std::unique_ptr<SendMessageArg> EXAMPLE();
#endif //API_QT_AUTOTEST

		protected:
			QString m_uploadType;
        };

		class InsertMessageArg : public PathArg<path_insert, InsertMessageArg>
		{
		public:
			InsertMessageArg();
			void build(const QString& link_path, QUrl& url)const override;

			/**
				The type of upload request to the /upload URI. Acceptable values are:
				media - Simple upload. Upload the media only, without any metadata.
				multipart - Multipart upload. Upload both the media and its metadata, in a single request.
				resumable - Resumable upload. Upload the file in a resumable fashion, using a series of
				at least two requests where the first request includes the metadata.
			*/
			QString getUploadType()const { return m_uploadType; }
			void    setUploadType(QString val) { m_uploadType = val; }

			/*
				Mark the email as permanently deleted (not TRASH) and only visible in Google Apps Vault 
				to a Vault administrator. Only used for Google Apps for Work accounts. (Default: false)
			*/
			bool    getDeleted()const { return m_deleted; }
			void    setDeleted(bool v) { m_deleted = v; }

			/*
				Source for Gmail's internal date of the message. 
				Acceptable values are:
				"dateHeader": The internal message time is based on the Date header in the email, when valid.
				"receivedTime": The internal message date is set to the time the message is received by Gmail. (default)
			*/
			QString getInternalDateSource()const { return m_internalDateSource; }
			void setInternalDateSource(QString s) { m_internalDateSource = s; }

#ifdef API_QT_AUTOTEST
			static std::unique_ptr<InsertMessageArg> EXAMPLE();
#endif //API_QT_AUTOTEST

		protected:
			QString m_uploadType;
			bool    m_deleted;
			QString m_internalDateSource;
		};

        class TrashMessageArg: public PathWithIdArg<path_trash, TrashMessageArg>
        {
        public:
            TrashMessageArg(QString idValue){m_id = idValue;}
        };

        class UntrashMessageArg: public PathWithIdArg<path_untrash, UntrashMessageArg>
        {
        public:
            UntrashMessageArg(QString idValue){m_id = idValue;}
        };

        class ImportMessageArg: public PathArg<path_import, ImportMessageArg>
        {
        public:
			ImportMessageArg();
			void build(const QString& link_path, QUrl& url)const override;
			//virtual QString arg()const override;
			/**
				The type of upload request to the /upload URI. Acceptable values are:
				media - Simple upload. Upload the media only, without any metadata.
				multipart - Multipart upload. Upload both the media and its metadata, in a single request.
				resumable - Resumable upload. Upload the file in a resumable fashion, using a series of
				at least two requests where the first request includes the metadata.
			*/
			QString getUploadType()const { return m_uploadType; }
			void    setUploadType(QString val) { m_uploadType = val; }

			/*
				Mark the email as permanently deleted (not TRASH) and only visible in Google Apps Vault
				to a Vault administrator. Only used for Google Apps for Work accounts. (Default: false)
			*/
			bool    getDeleted()const { return m_deleted; }
			void    setDeleted(bool v) { m_deleted = v; }

			/*
				Source for Gmail's internal date of the message.
				Acceptable values are:
				"dateHeader": The internal message time is based on the Date header in the email, when valid.
				"receivedTime": The internal message date is set to the time the message is received by Gmail. (default)
			*/
			QString getInternalDateSource()const { return m_internalDateSource; }
			void setInternalDateSource(QString s) { m_internalDateSource = s; }

			/*
				Ignore the Gmail spam classifier decision and never mark this email as SPAM in the mailbox. 
				(Default: false)
			*/
			bool    getNeverMarkSpam()const { return m_neverMarkSpam; }
			void    setNeverMarkSpam(bool v) { m_neverMarkSpam = v; }

			/*
				Process calendar invites in the email and add any extracted meetings to the Google Calendar 
				for this user. (Default: false)
			*/
			bool    getProcessForCalendar()const { return m_processForCalendar; }
			void    setProcessForCalendar(bool v) { m_processForCalendar = v; }

#ifdef API_QT_AUTOTEST
			static std::unique_ptr<ImportMessageArg> EXAMPLE();
#endif //API_QT_AUTOTEST

		protected:
			QString m_uploadType;
			bool    m_deleted;
			QString m_internalDateSource;
			bool    m_neverMarkSpam;
			bool    m_processForCalendar;
        };

        class BatchDeleteMessageArg: public PathArg<path_batchDelete, BatchDeleteMessageArg>
        {
        };

    };//common
};