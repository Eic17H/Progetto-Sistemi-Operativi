// Movimento della rana:
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