void setup()
{
    Serial.begin(9600);
    Serial.println("Teste 123");
}


void loop()
{

    int input = 0;

	if (Serial.available() > 0)
	{
                        
			input = Serial.read();

			switch(input)
			{
				case '0':
				case 0:
					Serial.println(analogRead(A0));
					break;
				case '1':
				case 1:
				case 't':
					Serial.println(analogRead(A1));
					break;
				case '2':
				case 2:
					Serial.println(analogRead(A2));
					break;
				case '3':
				case 3:
				case 'r':
					input = Serial.parseInt();
					analogWrite(3, input);
					break;
				case '4':
				case 4:
					input = Serial.read();
					analogWrite(4, input);
					break;
                case '13':
				case 13:
					Serial.println("Wat ");
                    break;
				default:
					Serial.print("Unknow input: ");
                    Serial.println((char)input);
			}
		
	}
}