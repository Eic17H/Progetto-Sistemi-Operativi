// Movimento

void movimentoRana(Pos* pos){
    Pos vel={0,0};
    bool staSaltando=false;
    while(1){
        if(nellaZonaCoccodrilli()){
            if(!staSaltando){
                vel.x = coccodrilloSuCuiSiTrova().vel + VELOCITA_CAMMINATA*direzioneInputOrizzontale();
                vel.y = 0;
                if(pulsanteSalto()){
                    staSaltando = true;
                    vel.y = VELOCITA_SALTO;
                }
            }else{
                if(haRaggiuntoUnCoccodrillo())
                    staSaltando = false;
            }
        }else{ // Nella zona delle tane
            vel.x = VELOCITA_CAMMINATA*direzioneInputOrizzontale();
            vel.y = VELOCITA_CAMMINATA*direzioneInputVerticale();
        }
        pos->x += vel.x;
        pos->y += vel.y;
    }
}

void movimentoCoccodrilli(Pos* pos){
    vel.x = MOLTIPLICATORE_DIFFICOLTA*velocitaRighe[];
    if(rigaDiQuestoCoccodrillo%2==1) vel.x *= -1;
    vel.y = 0;
    pos->x += vel.x;
    pos->y += vel.y;
}

// Tasti singoli

int direzioneInputOrizzontale(){
    int out = 0;
    if(getch()==INPUT_DESTRA) out += 1;
    if(getch()==INPUT_SINISTRA) out -= 1;
    return out;
}

int direzioneInputVerticale(){
    int out = 0;
    if(getch()==INPUT_GIU) out += 1;
    if(getch()==INPUT_SU) out -= 1;
    return out;
}

bool pulsanteSalto(){
    return (getch()==INPUT_SALTO);
}

// Check collisioni: ad ogni frame

// Se la rana tocca un proiettile, perde
void collisRanaProiettile(){
    Proiettile* p = malloc(sizeof(Proiettile)); // proiettile che sto controllando
    scorriLista(p, listaProiettiliCoccodrilliAttivi){
        if(distanzaPos(p.pos, rana.pos) < RAGGIO_PROIETTILE_COCCODRILLO + RAGGIO_RANA){
            perdi();
            stopScorriLista();
        }
    }
}

// Se c'è una coppia di proiettili che si scontrano, eliminali
void collisProiettileProiettile(){
    Proiettile* p = malloc(sizeof(Proiettile)); // proiettile che sto controllando
    Proiettile* r = malloc(sizeof(Proiettile)); // proiettile che sto controllando
    scorriLista(p, listaProiettiliCoccodrilliAttivi){
        scorriLista(r, listaProiettiliRanaAttivi){
                if(distanzaPos(p.pos, r.pos) < RAGGIO_PROIETTILE_COCCODRILLO + RAGGIO_PROIETTILE_RANA){
                elimina(p);
                elimina(r);
            }
        }
    }
}

// Se c'è almeno un coccodrillo su cui la rana si trova, non annega
void ranaCadeInAcqua(){
    Coccodrillo* c = malloc(sizeof(Coccodrillo));
    scorrilista(c, listaCoccodrilliSuQuestaRiga){
        if(distanzaPos(rana.pos, c.pos) < LARGHEZZA_COCCODRILLO/2+LARGHEZZA_RANA/2)
            return false;
    }
    return true;
}