#include "Portfolio.h"
#include <bits/stdc++.h>
#include "Checking.h"
#include "Investment.h"
#include "Savings.h"
Savings s[1024];
Checking ch[1024];
Investment in[1024];
bool Portfolio::importFile(const char *filename) {
  double a, b, a1, b1, j1, tmp = 0;
  char str[len], store[len], *first, *last;
  FILE *fd = stdin;
  int i, j, ncase;
  fd = fopen(filename, "r");  //////////////////
  if (fd == NULL) {
    cout << "Invalid file. No data imported" << endl;
    // cout << "False" << endl;
    return false;
  } else {
    fscanf(fd, "%d ", &ncase);
    for (i = 0; i < ncase; i++) {
      fgets(str, len, fd);
      str[strlen(str) - 1] = 0;
      last = strtok(str, ",");
      first = strtok(NULL, ",");
      first += 1;
      fscanf(fd, "%s ", store);
      //   printf("store = %s\n", store);
      if (strcmp(store, "Savings") == 0) {
        s[save].addf(first);
        s[save].addl(last);
        s[save].addt(store);
        fscanf(fd, "%lf %lf ", &a, &b);
        // printf("a = %lf, b = %lf\n", a, b);
        s[save].addbal(a);
        s[save].addr(b);
        vec.push_back('s');
        save++;
      } else if (strcmp(store, "Checking") == 0) {
        ch[check].addf(first);
        ch[check].addl(last);
        ch[check].addt(store);
        fscanf(fd, "%lf ", &a);
        // printf("a = %lf\n", a);
        ch[check].addbal(a);
        vec.push_back('c');
        check++;
      } else {
        in[invest].addf(first);
        in[invest].addl(last);
        in[invest].addt(store);
        for (j = 0; j < 5; j++) {
          fscanf(fd, "%lf %lf %lf %lf ", &a, &b, &a1, &b1);
          in[invest].A += a;
          in[invest].IVS += b;
          in[invest].CVS += a1;
          in[invest].I += b1;
          tmp += (a / b) * a1 + a * b1;
        }
        in[invest].ETF = tmp;
        vec.push_back('i');
        invest++;
      }
    }
  }
  // cout << "True" << endl;
  return true;
}
bool Portfolio::createReportFile(const char *filename) {
  fstream file;
  char buff[len], name[len];
  int i, j;
  double total_s = 0, total_c = 0, total_i = 0;
  double tmp = 0;
  file.open(filename, ios::out);
  if (!file) {
    cout << "Invalid file. No data imported" << endl;
    // cout << "False" << endl;
    return false;
  } else {
    file << "Banking Summary\n"
         << "------------------------\n";

    file << "Saving Accounts\n\n";
    file << left << setw(25) << "Holder's Name" << setw(20) << "Initial Balance"
         << setw(10) << "Projected Balance\n";
    file << "------------------------------------------------------------"
            "---------------\n";
    for (i = 0; i < save; i++) {
      strcpy(name, s[i].getf());
      name[strlen(name) - 1] = 0;
      strcat(name, " ");
      strcat(name, s[i].getl());
      name[strlen(name) - 1] = 0;
      file << left << setw(25) << name << setw(20) << fixed << setprecision(2)
           << s[i].getbalance() << setw(10) << s[i].ProjectedBalance() << endl;
      total_s += s[i].ProjectedBalance();
    }
    file << "Checking Accounts\n\n";
    file << left << setw(25) << "Holder's Name" << setw(20) << "Initial Balance"
         << setw(10) << "Projected Balance\n";
    file << "------------------------------------------------------------"
            "---------------\n";
    for (i = 0; i < check; i++) {
      strcpy(name, ch[i].getf());
      name[strlen(name) - 1] = 0;
      strcat(name, " ");
      strcat(name, ch[i].getl());
      name[strlen(name) - 1] = 0;
      file << left << setw(25) << name << setw(20) << ch[i].getbalance()
           << setw(10) << ch[i].ProjectedBalance() << endl;
      total_c += ch[i].ProjectedBalance();
    }
    file << "Investment Accounts\n\n";
    file << left << setw(25) << "Holder's Name" << setw(20) << "Initial Balance"
         << setw(10) << "Projected Balance\n";
    file << "------------------------------------------------------------"
            "---------------\n";
    for (i = 0; i < invest; i++) {
      strcpy(name, in[i].getf());
      name[strlen(name) - 1] = 0;
      strcat(name, " ");
      strcat(name, in[i].getl());
      name[strlen(name) - 1] = 0;
      file << left << setw(25) << name << setw(20) << fixed << setprecision(2)
           << in[i].A << setw(10) << in[i].ETF << endl;
      total_i += in[i].ETF;
    }
    file << "Overall Account distribution\n\n";
    file << left << setw(15) << "Savings:" << setw(15) << save << setw(10)
         << "-" << setw(10) << setw(10) << fixed << setprecision(2)
         << (total_s / save) << endl;
    file << setw(15) << "Checking:" << setw(15) << check << setw(10) << "-"
         << setw(10) << fixed << setprecision(2) << (total_c / check) << endl;
    file << setw(15) << "Investment:" << setw(15) << invest << setw(10) << "-"
         << setw(10) << fixed << setprecision(2) << (total_i / invest) << endl;
    // cout << "True" << endl;
  }
}
void Portfolio::menu() {
  cout << "*** Portfolio Management menu ***" << endl;
  cout << "I    Import accounts from a file" << endl;
  cout << "S    Show accounts (brief)" << endl;
  cout << "E    Export a banking report (to file)" << endl;
  cout << "M    Show this menu" << endl;
  cout << "Q    Quit program" << endl;
}
void Portfolio::showAccounts(vector<char> v) const {  // declare s
  int ss = 0, cc = 0, ii = 0;
  char name[len], n1, tmp;
  cout << left << setw(25) << "Holder" << setw(15) << "Type" << setw(10)
       << "Balance" << endl;
  cout << endl;
  for (int i = 0; i < v.size(); i++) {
    if (v[i] == 's') {
      strcpy(name, s[ss].getl());
      strcat(name, " ");
      strcat(name, s[ss].getf());
      name[strlen(name) - 1] = 0;
      cout << left << setw(25) << name << setw(15) << "Savings" << setw(10)
           << fixed << setprecision(2) << s[ss].getbalance() << endl;
      ss++;
    } else if (v[i] == 'c') {
      strcpy(name, ch[cc].getl());
      strcat(name, " ");
      strcat(name, ch[cc].getf());
      name[strlen(name) - 1] = 0;
      cout << left << setw(25) << name << setw(15) << "Checking" << setw(10)
           << ch[cc].getbalance() << endl;
      cc++;
    } else {
      strcpy(name, in[ii].getl());
      strcat(name, " ");
      strcat(name, in[ii].getf());
      name[strlen(name) - 1] = 0;
      cout << left << setw(25) << name << setw(15) << "Investment" << setw(10)
           << in[ii].A << endl;
      ii++;
    }
  }
}
