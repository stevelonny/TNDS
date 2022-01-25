#include "funzioni.hpp"
#include "integratore.hpp"

class FunzioneIntegrale : public FunzioneBase{
    public:
        FunzioneIntegrale(double x_1, double prec = 0.01) : m_x1{x_1} , m_prec{prec} {
            m_function = new Fun();
            m_trap = new Trapezoidi();
        }
        virtual ~FunzioneIntegrale() {
            delete m_function;
            delete m_trap;    
        }
        double Eval(double x) const override{
            return m_trap->Trapezoidi::Integrate(m_x1, x, m_prec, *m_function);
        }
    private:
        Trapezoidi * m_trap;
        Fun * m_function;
        double m_x1, m_prec;

};
