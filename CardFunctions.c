
int isBlack(Card c) {
    return c.type == 'S' || c.type == 'C';
}
int isRed(Card c) {
    return c.type == 'H' || c.type == 'D';
}
int isDifferent(Card c1, Card c2) {
    return c1.type != c2.type;
}
int isSequencial(Card lower, Card higher) {
    return higher.value == lower.value + 1;
}
int canFoundation(Card c) {
    return c.value == 13;
}
