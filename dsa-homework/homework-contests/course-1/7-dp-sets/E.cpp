#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

int n, k;
std::vector<std::vector<int>> ans;
std::vector<int> a, b;
std::unordered_map<std::string, int> elements;
std::unordered_map<int, std::string> elements_reversed;

int main() {
    elements["H"] = 1;
    elements["He"] = 2;
    elements["Li"] = 3;
    elements["Be"] = 4;
    elements["B"] = 5;
    elements["C"] = 6;
    elements["N"] = 7;
    elements["O"] = 8;
    elements["F"] = 9;
    elements["Ne"] = 10;
    elements["Na"] = 11;
    elements["Mg"] = 12;
    elements["Al"] = 13;
    elements["Si"] = 14;
    elements["P"] = 15;
    elements["S"] = 16;
    elements["Cl"] = 17;
    elements["Ar"] = 18;
    elements["K"] = 19;
    elements["Ca"] = 20;
    elements["Sc"] = 21;
    elements["Ti"] = 22;
    elements["V"] = 23;
    elements["Cr"] = 24;
    elements["Mn"] = 25;
    elements["Fe"] = 26;
    elements["Co"] = 27;
    elements["Ni"] = 28;
    elements["Cu"] = 29;
    elements["Zn"] = 30;
    elements["Ga"] = 31;
    elements["Ge"] = 32;
    elements["As"] = 33;
    elements["Se"] = 34;
    elements["Br"] = 35;
    elements["Kr"] = 36;
    elements["Rb"] = 37;
    elements["Sr"] = 38;
    elements["Y"] = 39;
    elements["Zr"] = 40;
    elements["Nb"] = 41;
    elements["Mo"] = 42;
    elements["Tc"] = 43;
    elements["Ru"] = 44;
    elements["Rh"] = 45;
    elements["Pd"] = 46;
    elements["Ag"] = 47;
    elements["Cd"] = 48;
    elements["In"] = 49;
    elements["Sn"] = 50;
    elements["Sb"] = 51;
    elements["Te"] = 52;
    elements["I"] = 53;
    elements["Xe"] = 54;
    elements["Cs"] = 55;
    elements["Ba"] = 56;
    elements["La"] = 57;
    elements["Ce"] = 58;
    elements["Pr"] = 59;
    elements["Nd"] = 60;
    elements["Pm"] = 61;
    elements["Sm"] = 62;
    elements["Eu"] = 63;
    elements["Gd"] = 64;
    elements["Tb"] = 65;
    elements["Dy"] = 66;
    elements["Ho"] = 67;
    elements["Er"] = 68;
    elements["Tm"] = 69;
    elements["Yb"] = 70;
    elements["Lu"] = 71;
    elements["Hf"] = 72;
    elements["Ta"] = 73;
    elements["W"] = 74;
    elements["Re"] = 75;
    elements["Os"] = 76;
    elements["Ir"] = 77;
    elements["Pt"] = 78;
    elements["Au"] = 79;
    elements["Hg"] = 80;
    elements["Tl"] = 81;
    elements["Pb"] = 82;
    elements["Bi"] = 83;
    elements["Po"] = 84;
    elements["At"] = 85;
    elements["Rn"] = 86;
    elements["Fr"] = 87;
    elements["Ra"] = 88;
    elements["Ac"] = 89;
    elements["Th"] = 90;
    elements["Pa"] = 91;
    elements["U"] = 92;
    elements["Np"] = 93;
    elements["Pu"] = 94;
    elements["Am"] = 95;
    elements["Cm"] = 96;
    elements["Bk"] = 97;
    elements["Cf"] = 98;
    elements["Es"] = 99;
    elements["Fm"] = 100;

    elements_reversed[1] = "H";
    elements_reversed[2] = "He";
    elements_reversed[3] = "Li";
    elements_reversed[4] = "Be";
    elements_reversed[5] = "B";
    elements_reversed[6] = "C";
    elements_reversed[7] = "N";
    elements_reversed[8] = "O";
    elements_reversed[9] = "F";
    elements_reversed[10] = "Ne";
    elements_reversed[11] = "Na";
    elements_reversed[12] = "Mg";
    elements_reversed[13] = "Al";
    elements_reversed[14] = "Si";
    elements_reversed[15] = "P";
    elements_reversed[16] = "S";
    elements_reversed[17] = "Cl";
    elements_reversed[18] = "Ar";
    elements_reversed[19] = "K";
    elements_reversed[20] = "Ca";
    elements_reversed[21] = "Sc";
    elements_reversed[22] = "Ti";
    elements_reversed[23] = "V";
    elements_reversed[24] = "Cr";
    elements_reversed[25] = "Mn";
    elements_reversed[26] = "Fe";
    elements_reversed[27] = "Co";
    elements_reversed[28] = "Ni";
    elements_reversed[29] = "Cu";
    elements_reversed[30] = "Zn";
    elements_reversed[31] = "Ga";
    elements_reversed[32] = "Ge";
    elements_reversed[33] = "As";
    elements_reversed[34] = "Se";
    elements_reversed[35] = "Br";
    elements_reversed[36] = "Kr";
    elements_reversed[37] = "Rb";
    elements_reversed[38] = "Sr";
    elements_reversed[39] = "Y";
    elements_reversed[40] = "Zr";
    elements_reversed[41] = "Nb";
    elements_reversed[42] = "Mo";
    elements_reversed[43] = "Tc";
    elements_reversed[44] = "Ru";
    elements_reversed[45] = "Rh";
    elements_reversed[46] = "Pd";
    elements_reversed[47] = "Ag";
    elements_reversed[48] = "Cd";
    elements_reversed[49] = "In";
    elements_reversed[50] = "Sn";
    elements_reversed[51] = "Sb";
    elements_reversed[52] = "Te";
    elements_reversed[53] = "I";
    elements_reversed[54] = "Xe";
    elements_reversed[55] = "Cs";
    elements_reversed[56] = "Ba";
    elements_reversed[57] = "La";
    elements_reversed[58] = "Ce";
    elements_reversed[59] = "Pr";
    elements_reversed[60] = "Nd";
    elements_reversed[61] = "Pm";
    elements_reversed[62] = "Sm";
    elements_reversed[63] = "Eu";
    elements_reversed[64] = "Gd";
    elements_reversed[65] = "Tb";
    elements_reversed[66] = "Dy";
    elements_reversed[67] = "Ho";
    elements_reversed[68] = "Er";
    elements_reversed[69] = "Tm";
    elements_reversed[70] = "Yb";
    elements_reversed[71] = "Lu";
    elements_reversed[72] = "Hf";
    elements_reversed[73] = "Ta";
    elements_reversed[74] = "W";
    elements_reversed[75] = "Re";
    elements_reversed[76] = "Os";
    elements_reversed[77] = "Ir";
    elements_reversed[78] = "Pt";
    elements_reversed[79] = "Au";
    elements_reversed[80] = "Hg";
    elements_reversed[81] = "Tl";
    elements_reversed[82] = "Pb";
    elements_reversed[83] = "Bi";
    elements_reversed[84] = "Po";
    elements_reversed[85] = "At";
    elements_reversed[86] = "Rn";
    elements_reversed[87] = "Fr";
    elements_reversed[88] = "Ra";
    elements_reversed[89] = "Ac";
    elements_reversed[90] = "Th";
    elements_reversed[91] = "Pa";
    elements_reversed[92] = "U";
    elements_reversed[93] = "Np";
    elements_reversed[94] = "Pu";
    elements_reversed[95] = "Am";
    elements_reversed[96] = "Cm";
    elements_reversed[97] = "Bk";
    elements_reversed[98] = "Cf";
    elements_reversed[99] = "Es";
    elements_reversed[100] = "Fm";

    std::cin >> n >> k;
    a.resize(n);
    b.resize(k);
    ans.resize(k);

    for (int i = 0; i < n; ++i) {
        std::string el;
        std::cin >> el;

        a[i] = elements[el];
    }

    for (int i = 0; i < k; ++i) {
        std::string el;
        std::cin >> el;

        b[i] = elements[el];
    }


    for (int mask = 1; mask < 1 << n; ++mask) {
        int sum = 0;
        for (int j = 0; j < n; ++j) {
            if (mask >> j & 1) {
                sum += a[j];
            }
        }

        for (int i = 0; i < k; ++i) {
            if (b[i] == sum) {
                ans[i].push_back(mask);
            }
        }
    }

    std::vector<std::vector<int>> dp(k + 1, std::vector<int>(1 << n, -1));
    dp[0][0] = 0;

    for (int i = 0; i < k; ++i) {
        for (int dp_mask = 0; dp_mask < 1 << n; ++dp_mask) {
            if (dp[i][dp_mask] == -1) continue;
            for (int mask : ans[i]) {
                if ((dp_mask & mask) != 0) continue;
                dp[i + 1][dp_mask | mask] = dp_mask;
            }
        }
    }

    std::vector<std::string> result(k);
    int cur_mask = (1 << n) - 1;
    if (dp[k][cur_mask] != -1) {
        std::cout << "YES\n";

        for (int ind = k - 1; ind >= 0; ind--) {
            int next_mask = dp[ind + 1][cur_mask];
            int mask = cur_mask ^ next_mask;
            bool first = true;
            std::string reaction = "";

            for (int j = 0; j < n; j++) {
                if (mask >> j & 1) {
                    if (!first) reaction += "+";
                    reaction += elements_reversed[a[j]];
                    first = false;
                }
            }

            reaction += "->" + elements_reversed[b[ind]];
            result[ind] = reaction;
            cur_mask = next_mask;
        }

        for (const auto& line : result) {
            std::cout << line << "\n";
        }
    } else {
        std::cout << "NO\n";
    }
}