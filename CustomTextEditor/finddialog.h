#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QLayout>
#include <QMap>         // for search history
#include <QPair>        // for search history

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    FindDialog(QWidget *parent = nullptr);
    ~FindDialog();
    inline QString getQueryText(){ return queryText; }
    inline void concludeReplaceAll() { replaceAllCanContinue = false; }

    // TODO make a SearchHistory class to encapsulate all of this logic
    inline void clearSearchHistory() { searchHistory.clear(); }
    void addToSearchHistory(QString term, int positionPriorToSearch, int firstMatchPosition);
    inline bool previouslyFound(QString term) { return searchHistory.find(term) != searchHistory.end(); }
    inline int positionPriorToFirstSearch(QString term) { return searchHistory[term].first; }
    inline int firstPositionOf(QString term){ return searchHistory[term].second; }
    inline QMap<QString, QPair<int, int>> *getSearchHistory() { return &searchHistory; }

signals:
    void startFinding(QString queryText, bool caseSensitive, bool wholeWords, QString failureMessage);
    void startReplacing(QString what, QString with, bool caseSensitive, bool wholeWords);

public slots:
    void on_findNextButton_clicked();
    void on_replaceButton_clicked();
    void on_replaceAllButton_clicked();

private:
    QLabel *findLabel;
    QLabel *replaceLabel;
    QPushButton *findNextButton;
    QPushButton *replaceButton;
    QPushButton *replaceAllButton;
    bool replaceAllCanContinue;
    QLineEdit *findLineEdit;
    QLineEdit *replaceLineEdit;
    QCheckBox *caseSensitiveCheckBox;
    QCheckBox *wholeWordsCheckBox;
    QString queryText;
    QHBoxLayout *findHorizontalLayout;
    QHBoxLayout *replaceHorizontalLayout;
    QHBoxLayout *optionsLayout;
    QVBoxLayout *verticalLayout;
    QMap<QString, QPair<int, int>> searchHistory;
};

#endif // FINDDIALOG_H
