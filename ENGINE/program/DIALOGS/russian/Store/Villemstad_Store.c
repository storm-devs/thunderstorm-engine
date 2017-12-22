// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("���������, ���� �� ������?",
                          "�� ������ ��� ��������� ��� ����. ��, ��������, ������������...", "������� �� ��� ������ ��� �������� � �����-�� �������...",
                          "��������, ��� �������, ����� ���� �������� ���-��. �� �������� ����!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("������, " + NPChar.name + ", ���-������ � ��������� ���.", "�����, ����� ���-��...",
                      "�� ��, ������������� � ������ ���...", "��, �� ����...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> ��������� ���� ��������� �������.
            if (pchar.questTemp.State == "Inquisition_toCuracao" || pchar.questTemp.State == "Inquisition_afterFrancisco")// ����� �2 ����. �������.
            {
                if (!CheckAttribute(pchar, "questTemp.State.Store"))
                {
                    dialog.text = "�� �� ������ �� �������� ����������. ��� ��� �����?";
        			link.l1 = "���� ����� " + GetFullName(pchar) + ". �� ������, ���� ���, ����� ������. ���� ������� ������ ���������� , ��� ������������ �������� ����, ������������ ��������� � 50 �����.";
        			link.l1.go = "Step_S2_1";
                }
                else
                {
                    if (CheckPassengerInCharacter(pchar, "JacowDeFonseka"))
                    {
                        dialog.text = "�� ������� ���! � ����� ���������� ���! ��� ��������� ����� 100 ����� �� ��� �����.";
            			link.l1 = "�� ��� ��, ���������. ���� ��� ����������, ��� ��� ��� ������ �����������.";
            			link.l1.go = "Step_S2_7";
                        AddMoneyToCharacter(pchar, 100000);
                        pchar.questTemp.State.Store = "Ok";
                        AddQuestRecord("Spa_Line_2_Inquisition", "14");
                        RemovePassenger(pchar, characterFromId("JacowDeFonseka"));
                    }
                    else
                    {
                        if (pchar.questTemp.State.Store != "Ok")
                        {
                            dialog.text = "�� ���-������ ������ � �����?";
                			link.l1 = "���� ���, �� � ���� ���������.";
                			link.l1.go = "exit";
                		}
                		else
                		{
                            dialog.text = "�� � ������ ���������� ���. ���� �� � ��������� � ��������� �������, ��� �� ����� ������� ��� ������� ������. �������.";
                			link.l1 = "�� ��� �������.";
                			link.l1.go = "exit";
                		}
                    }
                }
            }
            // <== ��������� ���� ��������� �������.
		break;
//*************************** ����� �2 �������, ������� ���������� ***************************
 		case "Step_S2_1":
    		dialog.text = "���� ��� ����� ������� ��������������� ��� �������� ����� ����, � �� � ����� ��������� ����� �����. � �� ��������� ����� � �� ��������� �� ����. ��� ��� ������ ������ � �������.";
    		link.l1 = "������, �� ������������� �������?";
    		link.l1.go = "Step_S2_2";
 		break;
 		case "Step_S2_2":
    		dialog.text = "���� �� � ���� ������������ ���� ����� �����, � �� ��������.";
    		link.l1 = "� ����, �� �� � ������ ���� ��������� ���� �������������, ���� ���. ���� ���� ���������, ��� � ������� ��� �����, ��-�� ���� ���� �������� ������������ �� ����� ��������, �� ����������� �� ������� ���� � �����, ���� �� �� �� �����, � ��� �� �� �� ���������. ���� ��� ������ ���� � ���� ������ ������, �� �� �������. � ����� ������, ���� �� �� ���������, �� ��� �������� ���� �����.";
    		link.l1.go = "Step_S2_3";
 		break;
 		case "Step_S2_3":
    		dialog.text = "� ��� ������� �������� ���, ��� � ���� ��� ����� �����.";
    		link.l1 = "���� ���� ����� ���� �� ������, � �� �� ���������� �� ���� � 50 �����, ��� �������, � ������ ���� �����.";
    		link.l1.go = "Step_S2_4";
 		break;
 		case "Step_S2_4":
    		dialog.text = "��������� �����������������, � � ���� �������� ����� ����� ��� ��� ���� ��������� �� ������������?";
    		link.l1 = "��, ����� �������� ������! � ��� ��� ����� ��������, ��� ��������� ���� ���������, ���� ����� �� �������!?";
    		link.l1.go = "Step_S2_5";
 		break;
 		case "Step_S2_5":
    		dialog.text = "� ���� ����� �� ��� �����... ���������, ��� �������, � ����� ����� �� ��������, ���������� ��� ��� �����.\n"+
                          "�� ������ ������ � ���� �� ����� ���� �������� ���� �����. �� ���� �� ����������� ��������� ���� ��� �������, �� � ���� ������� � ������ ��������� ������.";
    		link.l1 = "������.";
    		link.l1.go = "Step_S2_6";
 		break;
 		case "Step_S2_6":
    		dialog.text = "��� ���������, ���� ����� �� �������, ����� �� �������� ����� � ������ � ������. �� ������� � ������� �������. � ��������� �� ����.\n"+
                          "���� �� ��� ��������, �� ���� ����� ������ ������ ������� ��������� �����.";
    		link.l1 = "��, �������, ���������... ������ 50 ����� �� ���� � ������� �� �� ����������. �� �������.";
    		link.l1.go = "exit";
            AddQuestRecord("Spa_Line_2_Inquisition", "3");
            pchar.questTemp.State.Store = 1;
            Pchar.quest.Inquisition_fightForJacow.win_condition.l1 = "location";
            Pchar.quest.Inquisition_fightForJacow.win_condition.l1.location = "Panama_houseSp1";
            Pchar.quest.Inquisition_fightForJacow.win_condition = "Inquisition_fightForJacow";
 		break;
 		case "Step_S2_7":
    		dialog.text = "��, �������������. �� ������� ��� ������� ������, ������� �����. ������� ���.";
    		link.l1 = "�� ��� �������. ��������.";
    		link.l1.go = "exit";
            if (CheckCharacterItem(pchar, "Bible"))
            {
        		link.l2 = "����������, ���� ������ ���� ��������� ����� �����, ����� ������� ��� ��� ���������, �� ���� ����� ��...";
        		link.l2.go = "Step_S2_8";
            }
 		break;
 		case "Step_S2_8":
    		dialog.text = "� ���?";
    		link.l1 = "��, ��� � ����� ��� �������. ��������� � ����.";
    		link.l1.go = "Step_S2_9";
    		link.l2 = "�� ���, ������ ����������... ��������.";
    		link.l2.go = "exit";
 		break;
 		case "Step_S2_9":
    		dialog.text = "��� ��� ��!!! ����������, � ����� ��� ������ �� ���. ��� ����� ������ ���������� ��� ����� �����, �� ���� �� �������������, ����� ����� ������� ������ ���������, ����� �������� ���� ����������...";
    		link.l1 = "�� ������ ��, ����� ���� �����������. ���������.";
    		link.l1.go = "Step_S2_10";
 		break;
 		case "Step_S2_10":
    		dialog.text = "� ������� ����������, ��� ���, ��������� �� ���� ���������!!!\n"+
                          "����������, �� ������ �����, ��� ������� �� ������ ���� ������� ���������� ���� �������...";
    		link.l1 = "����?!!";
    		link.l1.go = "Step_S2_11";
    		TakeItemFromCharacter(pchar, "Bible");
 		break;
 		case "Step_S2_11":
    		dialog.text = "��-��, ���� �������. � � � �������� ������ ��� ���!";
    		link.l1 = "� �������� ������� ��� ���... �������, � �����, ���-�� � ���� ������ ���� ������...";
    		link.l1.go = "Step_S2_12";
    		AddMoneyToCharacter(pchar, 1000000);
 		break;
 		case "Step_S2_12":
    		dialog.text = "�����, ���� ���. ��������, ��� ���� ������ ��� ���������� �� ���� �����! ��, � ����������� ����, ��� ������ ��������, ����� ��� ������, ��� ��������� �������� ������� ������ ������...";
    		link.l1 = "��������, �� ���� ��� ������...";
    		link.l1.go = "exit";
 		break;

	}
	UnloadSegment(NPChar.FileDialog2);
}

