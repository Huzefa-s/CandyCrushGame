#ifndef CANDY_H
#define CANDY_H

class Candy {
public:
    Candy(int type);
    int getType() const;
    void setType(int type);

private:
    int type;
};

#endif
