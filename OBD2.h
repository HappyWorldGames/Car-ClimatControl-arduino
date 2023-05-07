#pragma once

class TempListener {
	public:
		virtual void onTempListener(int temp);
};

class OBD2 {
	private:
		TempListener *tempListener = NULL;
		
		boolean startText(String text, String startText) {
			if(text.length() < startText.length()) return false;
				for(int i = 0; i < text.length(); i++) {
					if(text[i] == startText[0]) {
						String mText = "";
						for(int j = 0; j < startText.length(); j++) {
							mText += text[i + j];
						}
						if(mText.equals(startText)) return true;
					}
				}
			return false;
		}
		
	public:
		OBD2() {
			
		}
		
		void onData(String data) {
			if(startText(data, "")){
				if(tempListener != NULL) {
					int temp = TODO();
					tempListener(temp);
				}
			}
		}
		
		void setOnTempListener(TempListener tempListener) {
			this->tempListener = tempListener;
		}
		
};
