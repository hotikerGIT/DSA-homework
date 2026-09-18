#include <iostream>

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int x = 0b111111111111111000000000000000;
        std::cout << x << std::endl;

        int v_stripe;
        int m_stripe;
        int m0 = 0, m1;
        std::cin >> v_stripe;

        if (v_stripe > x) {
            m1 = 1;

            std::cout << m0 << std::endl << m1 << std::endl;

            std::cin >> m_stripe;

            std::cout << (m_stripe % 2 == v_stripe % 2 ? 0 : 1) << std::endl;
        }
        else if (v_stripe < x) {
            m1 = 1 << 29;

            std::cout << m0 << std::endl << m1 << std::endl;

            std::cin >> m_stripe;

            std::cout << (m_stripe >> 29 == v_stripe >> 29 ? 0 : 1) << std::endl;
        }

        else {
            m1 = (1 << 29) + 1;

            std::cout << m0 << std::endl << m1 << std::endl;

            std::cin >> m_stripe;

            bool has_first = (m_stripe >> 15) > 0;
            bool has_second = (m_stripe & ((1 << 15) - 1)) > 0;

            std::cout << (has_second && has_first ? 1 : 0) << std::endl;
        }
    }
}