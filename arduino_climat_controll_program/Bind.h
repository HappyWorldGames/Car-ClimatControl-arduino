#pragma once

class Bind {
	private:
		Setting *setting = NULL;
		
		int nextInt() {
			return Serial.parseInt();
		}
		
		void onNormal(int cmd) {
			switch(cmd) {
				
			}
		}
		
		void onService(int cmd) {
			switch(cmd) {
				
			}
		}
		
	public:
		
		Bind(Setting setting) {
			this->setting = &setting;
		}
		
		/*
		*	sytem command:
		*		1 = normal mode
		*		0 = service mode
		*/
		bool waitCommand() {
			if(!Serial.available()) return false;
			int cmd = nextInt();
			switch(cmd) {
				case 1:
				case 0:
					setting->data.mode = cmd;
					break;
				default:
					switch(setting->data.mode) {
						case 1:
							onNormal(cmd);
							break;
						case 0:
							onService(cmd);
							break;
					}
					break;
			}
			return true;
		}
};
