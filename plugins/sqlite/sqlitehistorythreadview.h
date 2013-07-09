#ifndef SQLITEHISTORYTHREADVIEW_H
#define SQLITEHISTORYTHREADVIEW_H

#include <HistoryThreadView>
#include <HistoryItem>
#include <HistorySort>
#include <HistoryFilter>
#include <QSqlQuery>

class SQLiteHistoryReader;

class SQLiteHistoryThreadView : public HistoryThreadView
{
public:
    SQLiteHistoryThreadView(SQLiteHistoryReader *reader,
                            HistoryItem::ItemType type,
                            const HistorySort &sort,
                            const HistoryFilter &filter);

    QList<HistoryThreadPtr> nextPage();
    bool isValid() const;

private:
    HistoryItem::ItemType mType;
    HistorySort mSort;
    HistoryFilter mFilter;
    QSqlQuery mQuery;
    int mPageSize;
    SQLiteHistoryReader *mReader;
};

#endif // SQLITEHISTORYTHREADVIEW_H