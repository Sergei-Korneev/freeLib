#include "treebookitem.h"

#include <QCollator>
#include <QHeaderView>

#include "library.h"

TreeBookItem::TreeBookItem(QTreeWidget *parent, int type)
    :QTreeWidgetItem(parent, type)
{

}

TreeBookItem::TreeBookItem(QTreeWidgetItem *parent, int type)
    :QTreeWidgetItem(parent, type)
{

}

bool TreeBookItem::operator<(const QTreeWidgetItem &other) const
{
    static QCollator collator;
    auto sortColumn = treeWidget()->sortColumn();

    if(type() == ITEM_TYPE_BOOK && other.type() == ITEM_TYPE_SERIA && parent()->type() == ITEM_TYPE_AUTHOR){
        auto header  = treeWidget()->header();
        auto sortOrder  = header->sortIndicatorOrder();
        return sortOrder == Qt::DescendingOrder;
    }
    if(type() == ITEM_TYPE_SERIA && other.type() == ITEM_TYPE_BOOK && other.parent()->type() == ITEM_TYPE_AUTHOR){
        auto header  = treeWidget()->header();
        auto sortOrder  = header->sortIndicatorOrder();
        return sortOrder == Qt::AscendingOrder;
    }

    if(type() == ITEM_TYPE_BOOK && other.type() == ITEM_TYPE_BOOK){
        SBook& bookThis = mLibs[idCurrentLib].mBooks[data(0, Qt::UserRole).toUInt()];
        SBook& bookOther = mLibs[idCurrentLib].mBooks[other.data(0, Qt::UserRole).toUInt()];
        switch(sortColumn){
        case 0:  //Название книги
            return collator.compare(text(0), other.text(0)) < 0;
        case 1: //Номер в серии
            return bookThis.numInSerial < bookOther.numInSerial;
        case 2: //Размер
            return bookThis.nSize < bookOther.nSize;
        case 3: //рейтинг
            return bookThis.nStars < bookOther.nStars;
        case 4: //дата добавления
            return bookThis.date < bookOther.date;
        case 5: //Жанр
            return collator.compare(mGenre[bookThis.listIdGenres.first()].sName, mGenre[bookOther.listIdGenres.first()].sName) < 0;
        case 6: //Язык
            return mLibs[idCurrentLib].vLaguages[bookThis.idLanguage] < mLibs[idCurrentLib].vLaguages[bookOther.idLanguage];
        }

    }
    if(type() == ITEM_TYPE_AUTHOR && other.type() == ITEM_TYPE_AUTHOR){
        auto header  = treeWidget()->header();
        auto sortOrder  = header->sortIndicatorOrder();
        switch(sortColumn){
        case 0:  //Название книги
            return collator.compare(text(0), other.text(0)) < 0;
        default:
            return (collator.compare(text(0), other.text(0)) < 0) != (sortOrder == Qt::DescendingOrder);
        }
    }
    if(type() == ITEM_TYPE_SERIA && other.type()== ITEM_TYPE_SERIA){
        auto header  = treeWidget()->header();
        auto sortOrder  = header->sortIndicatorOrder();
        switch(sortColumn){
        case 0:  //Название книги
            return collator.compare(text(0), other.text(0)) < 0;
        default:
            return (collator.compare(text(0), other.text(0)) < 0) != (sortOrder == Qt::DescendingOrder);
        }
    }
    return true;
}
