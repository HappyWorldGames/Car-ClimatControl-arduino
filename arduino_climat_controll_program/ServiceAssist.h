
/*
 * Commands:
 * 	1 - переключиться на обычный режим
 * 	2 - тест Серво-Привода заслонки тепло-холод
 *	3 - тест OBD2
 */
class ServiceAssist {
	private:
		int testMode = 0;
	
		void print(String text) {
			Serial.print(text);
		}
		
		void println(String text) {
			print(text + '\n');
		}
	
		void switchMode() {
			TODO();
		}
		
		void testServoTemp() {
			TODO();
		}
		
		void testOBD2() {
			TODO();
		}
		
	public:
		ServiceAssist() {
			
		}

		void cmd(int[] cmds) {
			if(testMode != 0){
				
			}else switch(cmds[0]) {
				case 1:
					switchMode();
					break;
				case 2:
					testServoTemp();
					break;
				case 3:
					testOBD2();
					break;
			}
		}
};