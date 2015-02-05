class player
{
	public:
		player(double HP = 100, double speed = 1);
		void HP_minus(double damaged);
		double HP_left();
		void draw_player();

	private:
		double HP;
		double speed;
};