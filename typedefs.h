#ifndef __TYPEDEFS_H__
#define __TYPEDEFS_H__

enum Token_Type {OPEN_TAG, CLOSE_TAG, EMPTY_TAG,
                  WORD_TOKEN, SPACE_STR, NL_TOKEN, ERR_TOKEN};

std::string human_readable[7] = {"BEGIN TAG", "END TAG", "EMPTY TAG",
                            "WORD", "SPACE STRING", "NEWLINE", "ERROR"};

enum Char_Type {LB, FS, RB, AL, SP, NL, OT, ERR};

enum State_Name {
    /*00*/ START,
    /*01*/ OT1,
    /*02*/ OT2,
    /*03*/ OT3,
    /*04*/ CT1,
    /*05*/ CT2,
    /*06*/ CT3,
    /*07*/ ET1,
    /*08*/ SP1,
    /*09*/  W1,
    /*10*/ OTF,
    /*11*/ CTF,
    /*12*/ ETF,
    /*13*/ SPF,
    /*14*/   W,
    /*15*/  WF,
    /*16*/ NLF,
    /*17*/ ERF
    };

Char_Type char_classes[256] = {
// this is a one dimensional array arranged in table form for readabiltiy
/*          0   1   2   3   4   5   6   7   8   9  */
/*000-0F*/  OT, OT, OT, OT, OT, OT, OT, OT, OT, SP,
/*010-19*/  NL, OT, OT, OT, OT, OT, OT, OT, OT, OT,
/*020-29*/  OT, OT, OT, OT, OT, OT, OT, OT, OT, OT,
/*030-39*/  OT, OT, SP, OT, OT, OT, OT, OT, OT, OT,
/*040-49*/  OT, OT, OT, OT, OT, OT, OT, FS, OT, OT,
/*050-59*/  OT, OT, OT, OT, OT, OT, OT, OT, OT, OT,
/*060-69*/  LB, OT, RB, OT, OT, AL, AL, AL, AL, AL,
/*070-89*/  AL, AL, AL, AL, AL, AL, AL, AL, AL, AL,
/*080-89*/  AL, AL, AL, AL, AL, AL, AL, AL, AL, AL,
/*090-99*/  AL, OT, OT, OT, OT, OT, OT, AL, AL, AL,
/*100-09*/  AL, AL, AL, AL, AL, AL, AL, AL, AL, AL,
/*110-19*/  AL, AL, AL, AL, AL, AL, AL, AL, AL, AL,
/*120-29*/  AL, AL, AL, OT, OT, OT, OT, OT,ERR,ERR,

/*130-39*/ ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
/*140-49*/ ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
/*150-59*/ ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
/*160-69*/ ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
/*170-79*/ ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
/*180-89*/ ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
/*190-99*/ ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
/*200-09*/ ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
/*210-19*/ ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
/*220-29*/ ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
/*230-39*/ ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
/*240-49*/ ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
/*250-55*/ ERR,ERR,ERR,ERR,ERR,ERR,
};

State_Name state_trans[17][8] = {
    /*             LB    FS    RB   AL    SP    NL    OT    ER
              -------------------------------------------------
/*01  START */   OT1,  W1,    W1,  W1,   SP1,  NLF,  W1,   ERF,
/*02    OT1   */   WF,   CT1,   W1,  OT2,  WF,   WF,   W1,   ERF,
/*03    OT2   */   ERF,  ET1,  OTF,  OT2,  OT3,  ERF,  ERF,  ERF,
/*04    OT3   */   ERF,  ERF,  OTF,  ERF,  OT3,  ERF,  ERF,  ERF,
/*05    CT1   */   ERF,  ERF,  ERF,  CT2,  ERF,  ERF,  ERF,  ERF,
/*06    CT2   */   ERF,  ERF,  CTF,  CT2,  CT3,  ERF,  ERF,  ERF,
/*07    CT3   */   ERF,  ERF,  CTF,  ERF,  CT3,  ERF,  ERF,  ERF,
/*08    ET1   */   ERF,  ERF,  ETF,  ERF,  ERF,  ERF,  ERF,  ERF,
/*09    SP1   */   SPF,  SPF,  SPF,  SPF,  SP1,  SPF,  SPF,  ERF,
/*10     W1   */    WF,   W1,   W1,   W1,   WF,   WF,   W1,  ERF,
/*11    OTF   */   ERF,  ERF,  ERF,  ERF,  ERF,  ERF,  ERF,  ERF,
/*12    CTF   */   ERF,  ERF,  ERF,  ERF,  ERF,  ERF,  ERF,  ERF,
/*13    ETF   */   ERF,  ERF,  ERF,  ERF,  ERF,  ERF,  ERF,  ERF,
/*14    SPF   */   ERF,  ERF,  ERF,  ERF,  ERF,  ERF,  ERF,  ERF,
/*15     WF   */   ERF,  ERF,  ERF,  ERF,  ERF,  ERF,  ERF,  ERF,
/*16    NLF   */   ERF,  ERF,  ERF,  ERF,  ERF,  ERF,  ERF,  ERF,
/*17    ERF   */   ERF,  ERF,  ERF,  ERF,  ERF,  ERF,  ERF,  ERF,};



struct Token {
    Token_Type type;
    std::string lexeme;
    long line_number;
    int char_pos;
};


#endif // __TYPEDEFS_H__
