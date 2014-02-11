#include "UTestResetCatapult.h"

UTestResetCatapult::UTestResetCatapult() : CommandGroup("UTest Reset Catapult") {
	m_command = new ResetCatapult();
	AddSequential(m_command);
}

void UTestResetCatapult::Initialize() {
	// distance is in encoder units, 1 unit = N of pulses in 1 sec at top speed.
	m_command->Reset(
			
		);
}
