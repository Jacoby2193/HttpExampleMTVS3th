// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpWidget.h"
#include "Components/Button.h"
#include "HttpActor.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "JsonParseLib.h"
#include "Engine/Texture2D.h"
#include "Components/Image.h"

void UHttpWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// 버튼을 연결하고싶다.
	ButtonSend->OnClicked.AddDynamic(this, &UHttpWidget::OnMyClickSend);

	ButtonPostSend->OnClicked.AddDynamic(this, &UHttpWidget::OnMyClickSendPost);

	ButtonGetWebImage->OnClicked.AddDynamic(this, &UHttpWidget::OnMyClickGetWebImage);
}

void UHttpWidget::OnMyClickSend()
{
	// HttpActor에게 공공데이터값을 받아오라고 요청하라고 하고싶다.
	FString fullURL = FString::Printf(TEXT("%s?serviceKey=%s&pageNo=%s&numOfRows=%s"), *URL, *Key, *EditPageNo->GetText().ToString(), *EditNumOfRows->GetText().ToString());

	UE_LOG(LogTemp, Warning, TEXT("%s"), *fullURL);

	HttpActor->ReqNewBookInfo(fullURL);
}

void UHttpWidget::OnMyClickSendPost()
{
	TMap<FString, FString> studentData;
	studentData.Add("Name", "Kei");
	studentData.Add("Age", "23");
	studentData.Add("Height", "185");
	FString json = UJsonParseLib::MakeJson(studentData);

	HttpActor->ReqPostTest(ServerURL, json);
}

void UHttpWidget::OnMyClickGetWebImage()
{
	HttpActor->ReqGetWebImage(WebImageURL);
}

void UHttpWidget::SetWebImage(UTexture2D* newTexture)
{
	ImageWeb->SetBrushFromTexture(newTexture);
}

void UHttpWidget::SetTextLog(FString log)
{
	TextLog->SetText(FText::FromString(log));
}

void UHttpWidget::SetHttpActor(AHttpActor* actor)
{
	HttpActor = actor;
}
