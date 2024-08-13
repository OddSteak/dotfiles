#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* quotes[] = {
    "I see a red door and I want it painted black.",
    "Stayin' alive, stayin' alive",
    "Is this the real life, is this just fantasy",
    "What's in your head, in your head?",
    "Two trailer park girls go round the outside",
    "Here we go back, this is the moment, tonight is the night",
    "Now you're just somebody that I used to know...",
    "Some legends are told, some turn to dust or to gold",
    "Your brain gets smart, but your head gets dumb.",
    "I'm beggin', beggin' you",
    "Never gonna let you down (I am trying!)",
    "\"I use Arch, btw\" - Modi Ji",
    "\"Hyper\".replace(\"e\", \"\")",
    "\"my win11 install runs hyprland that is true\" - raf",
    "Choosing…it has always hurt. And always will.",
    "Black and white and grey, all the shades of truth.",
    "When the snows fall and the white winds blow,\n  the lone wolf dies, but "
        "the pack survives",
    "The Drowned God did not answer. He seldom did.\n\tThat was the trouble "
        "with gods.",
    "There was no slavery in the free city of Pentos.\n\tNonetheless, they "
        "were slaves.",
    "\"Edd, fetch me a block\" - Jon Snow",
    "Egg, I dreamed that I was old.",
    "Almost dead yesterday, maybe dead tomorrow,\n   but alive, gloriously "
        "alive, today.",
    "Take what you want, and pay for it.",
    "Oh, my sweet summer child, What do you know of fear?",
    "Dance with me then",
    "An idiot admires complexity, a genius admires simplicity",
    "It'll all be yesteryear soon",
    "A little less than a human being",
    "Abandon All Hope, Ye Who Enter Here",
    "To rice, or not to rice, that is the question",
};

int main()
{
    srand(time(NULL));
    int random_num = rand() % (sizeof(quotes) / sizeof(quotes[0]));
    printf("%s", quotes[random_num]);
    return 0;
}
