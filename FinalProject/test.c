#include <stdio.h>
#include <string.h>

typedef struct nba_player_s {
	int Rk; // Rank (we're not sorting, so more of an ID for us)
	char Player[128]; // Player name - include first and last name so ("%s %s") and then convert to Player[]
	int Age; // Age
	int G; // Games played
	int GS; // Games started
	int MP; // Minutes played
	int FG; // Field goals (baskets)
	int FGA; // Field goal attempts (shots)
	float FGP; // Field-goal percentage
	int Three_P; // Three Points 
	int Three_PA; // Three Point Attempts
	float Three_PAP; // Three Point Percentage
	int Two_P; // Two Points
	int Two_PA; // Two Point Attempts
	float Two_PAP; // Two Point Percentage
	float eFGP; //  
	int FT; // Free Throws
	int FTA; // Free Throw Attempts
	float FTP; // Free Throw Percentage
	int ORB; // Offensive Rebounds
	int DRB; // Defensice Rebounds
	int TRB; // Total Rebounds
	int AST; // Assists 
	int STL; // Steals
	int BLK; // Blocks
	int TOV; // Turnovers
	int PF; //
	int PTS; // Points
} nba_player;


nba_player ReadStruct(FILE *infile);
void PrintStruct(nba_player player);

nba_player ReadStruct(FILE *infile) {
	nba_player pl;
	char first[128], last[128]; // You'll need to grab these separately and then convert to .Player
	
	// Data format:
	//Rk,Player,Age,G,GS,MP,FG,FGA,FG%,3P,3PA,3P%,2P,2PA,2P%,eFG%,FT,FTA,FT%,ORB,DRB,TRB,AST,STL,BLK,TOV,PF,PTS	
	// Don't try to fit this all on one line!
	fscanf(infile, "%d,%s %s,%d,%d,%d,%d,%d,%.3f,%d,%d,%.3f,%d,%d,%.3f,%.3f,%d,%d,%.3f,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		&pl.Rk, pl.Player, &pl.Age, &pl.G, &pl.GS, &pl.MP, &pl.FG, &pl.FGA, &pl.FGP, &pl.Three_P, &pl.Three_PA, &pl.Three_PAP,
		&pl.Two_P, &pl.Two_PA, &pl.Two_PAP, &pl.eFGP, &pl.FT, &pl.FTA, &pl.FTP, &pl.ORB, &pl.DRB, &pl.TRB, &pl.AST,
		&pl.STL, &pl.BLK, &pl.TOV, &pl.PF, &pl.PTS);

	// Process first and last into pl.Player. sprintf() is fine for this. 
	//sprintf(pl.Player,...)
	
	return pl;	
}
void PrintStruct(nba_player pl) {
	printf("\nPlayer: %s\n", pl.Player);
	printf("  Age: %d\n", pl.Age);
	printf("  G (GS): %d (%d)\n", pl.G, pl.GS);
	printf("  FG / FGA (FG%%): %d / %d (%2.1f%%)\n", pl.FG, pl.FGA, 100*pl.FGP);
	printf("  3P / 3PA (3P%%): %d / %d (%2.1f%%)\n", pl.Three_P, pl.Three_PA, 100*pl.Three_PAP);
	printf("  2P / 2PA (2P%%): %d / %d (%2.1f%%)\n", pl.Two_P, pl.Two_PA, 100*pl.Two_PAP);
	printf("  FT / FTA (FT%%): %d / %d (%2.1f%%)\n", pl.FT, pl.FTA, 100*pl.FTP);
	printf("  TRB - ORB, DRB: %d - %d, %d\n", pl.TRB, pl.ORB, pl.DRB);
	printf("  AST, STL, BLK, TOV: %d, %d, %d, %d\n", pl.AST, pl.STL, pl.BLK, pl.TOV);
	
	return;
}


int main(void) {

	int ID = 1;
	while (1) {
		printf("Player %d> ", ID++);
		nba_player player = ReadStruct(stdin);

		//What is our exit / break condition?
		if(strcmp(player.Player, "   ") == 0){
			break;
		}
		
		
		PrintStruct(player);
	}
	return 0;
}


	 
	 