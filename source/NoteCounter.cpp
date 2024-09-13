#include "syati.h"

void NoteCounter_init(LayoutActor* pActor, const Nerve* pInitNerve)
{
	MR::connectToSceneLayout(pActor);
	pActor->initLayoutManager("NoteCounter", 2);
	pActor->initNerve(pInitNerve);
	MR::createAndAddPaneCtrl(pActor, "ShaDigitL", 2);
	MR::createAndAddPaneCtrl(pActor, "ShaDigitR", 2);
}

void NoteCounter_exeHideToShow(LayoutActor* pActor)
{
	MR::startAnimAtFirstStep(pActor, "Appear", 0);
	MR::setTextBoxFormatRecursive(pActor, "Counter", L"%02d", 0);
}

void NoteCounter_exeShowToHide(LayoutActor* pActor)
{
	MR::startAnimAtFirstStep(pActor, "End", 0);
}

bool NoteCounter_declareNoteNumMaxAndMelody(NoteCounter* pLayout, const Nerve* pNerve)
{
	MR::startPaneAnim(pLayout, "ShaDigitL", "DigitL", 0);
	MR::startPaneAnim(pLayout, "ShaDigitR", "DigitR", 0);

	int ones = (pLayout->mNoteNumMax % 10);
	int tens = (pLayout->mNoteNumMax / 10) % 10;

	MR::setPaneAnimFrameAndStop(pLayout, "ShaDigitL", static_cast<f32>(tens), 0);
	MR::setPaneAnimFrameAndStop(pLayout, "ShaDigitR", static_cast<f32>(ones), 0);

	return pLayout->isNerve(pNerve);
}

void NoteCounter_add(NoteCounter* pLayout)
{
	MR::setTextBoxFormatRecursive(pLayout, "Counter", L"%02d", pLayout->mNoteNum);
	MR::startAnim(pLayout, "Flash", 0);

	pLayout->tryEndDisp();
}

#if defined(KOR) || defined(TWN)
kmCall(0x804857E8 +0x10, NoteCounter_init);
kmCall(0x80485AF4 + 0x10, NoteCounter_exeHideToShow);
kmWrite32(0x80485AF8 + 0x10, 0x48000064);
kmCall(0x80485A1C + 0x10, NoteCounter_exeShowToHide);
kmWrite32(0x80485A20 + 0x10, 0x48000064);
kmCall(0x80485854 + 0x10, NoteCounter_declareNoteNumMaxAndMelody);
kmCall(0x804859E0 + 0x10, NoteCounter_add);
#elif
kmCall(0x804857E8, NoteCounter_init);
kmCall(0x80485AF4, NoteCounter_exeHideToShow);
kmWrite32(0x80485AF8, 0x48000064);
kmCall(0x80485A1C, NoteCounter_exeShowToHide);
kmWrite32(0x80485A20, 0x48000064);
kmCall(0x80485854, NoteCounter_declareNoteNumMaxAndMelody);
kmCall(0x804859E0, NoteCounter_add);
#endif