#include "syati.h"
#include "Game/Screen/NoteCounterExt.h"

#if defined TWN || defined KOR
#define REGIONOFF 0x10
#else
#define REGIONOFF 0
#endif

NoteCounterExt::NoteCounterExt(const char* pName) : NoteCounter(pName) {
	mPaneRumbler = 0;
}

NoteCounterExt* createNoteCounterExt() {
	return new NoteCounterExt("音符カウンタ");
}

NoteCounterExt::~NoteCounterExt() {}
void NoteCounterExt::control() {
	mPaneRumbler->update();
}

void NoteCounter_init(NoteCounterExt* pLayout, const Nerve* pInitNerve)
{
	MR::connectToSceneLayout(pLayout);
	pLayout->initLayoutManager("NoteCounter", 2);
	pLayout->initNerve(pInitNerve);
	MR::createAndAddPaneCtrl(pLayout, "ShaDigitL", 2);
	MR::createAndAddPaneCtrl(pLayout, "ShaDigitR", 2);
	MR::createAndAddPaneCtrl(pLayout, "Counter", 1);
	MR::hideLayout(pLayout);
	pLayout->mPaneRumbler = new CountUpPaneRumbler(pLayout, "Counter");
	pLayout->mPaneRumbler->mRumbleCalculator->mRumbleStrength = 8.0f;
}

void NoteCounter_exeHideToShow(NoteCounterExt* pLayout)
{
	MR::startAnimAtFirstStep(pLayout, "Appear", 0);
	MR::setTextBoxFormatRecursive(pLayout, "Counter", L"%02d", 0);
}

void NoteCounter_exeShowToHide(NoteCounterExt* pLayout)
{
	pLayout->mPaneRumbler->reset();
	MR::startAnimAtFirstStep(pLayout, "End", 0);
}

bool NoteCounter_declareNoteNumMaxAndMelody(NoteCounterExt* pLayout, const Nerve* pNerve)
{
	MR::startPaneAnim(pLayout, "ShaDigitL", "DigitL", 0);
	MR::startPaneAnim(pLayout, "ShaDigitR", "DigitR", 0);

	int ones = (pLayout->mNoteNumMax % 10);
	int tens = (pLayout->mNoteNumMax / 10) % 10;

	MR::setPaneAnimFrameAndStop(pLayout, "ShaDigitL", static_cast<f32>(tens), 0);
	MR::setPaneAnimFrameAndStop(pLayout, "ShaDigitR", static_cast<f32>(ones), 0);

	return pLayout->isNerve(pNerve);
}

void NoteCounter_add(NoteCounterExt* pLayout)
{
	MR::setTextBoxFormatRecursive(pLayout, "Counter", L"%02d", pLayout->mNoteNum);
	MR::startAnim(pLayout, "Flash", 0);
	pLayout->mPaneRumbler->start();

	pLayout->tryEndDisp();
}

kmCall(0x804857E8+REGIONOFF, NoteCounter_init);
kmCall(0x80485AF4+REGIONOFF, NoteCounter_exeHideToShow);
kmWrite32(0x80485AF8+REGIONOFF, 0x48000064);
kmCall(0x80485A1C+REGIONOFF, NoteCounter_exeShowToHide);
kmWrite32(0x80485A20+REGIONOFF, 0x48000064);
kmCall(0x80485854+REGIONOFF, NoteCounter_declareNoteNumMaxAndMelody);
kmCall(0x804859E0+REGIONOFF, NoteCounter_add);
kmCall(0x80471760+REGIONOFF, createNoteCounterExt);
kmWrite32(0x80471764+REGIONOFF, 0x48000014);