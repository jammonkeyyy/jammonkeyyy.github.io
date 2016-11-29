#include "PlayList.h"
#include<iostream>
#include <VersionHelpers.h>		//�����жϵ�ǰWindows�İ汾

int main()
{
	CPlayer my_player;
	my_player.ShowInfo();
	my_player.ShowPlaylist();
	while(!my_player.ErrorDispose());
	my_player.MusicControl(Command::OPEN);
	my_player.IniLyrics();
	my_player.MusicControl(Command::SEEK);
	my_player.ShowProgressBar();
	my_player.SetVolume();
	int sec_current, sec_temp;		//���ڿ��ƽ�����Ϣˢ��Ƶ�ʣ���ǰ��������ÿ��1��ˢ��
	sec_temp = my_player.GetCurrentSecond();
	SYSTEMTIME current_time, temp_time;		//���ڿ��Ƹ��ˢ��Ƶ�ʣ����ÿ��LYRIC_REFRESH����ˢ��
	int width(0), hight(0);
	int width_t, hight_t;
	GetLocalTime(&temp_time);
	while (true)
	{
		while(!my_player.ErrorDispose());
		my_player.GetCurrentPosition();
		sec_current = my_player.GetCurrentSecond();
		if (sec_temp != sec_current)		//��ȡ����ʱ����������������������ˢ��һ�ν�����Ϣ
		{
			sec_temp = sec_current;
			my_player.GetCurrentPosition();
			my_player.ShowInfo();
			//my_player.ShowPlaylist();
			my_player.ShowProgressBar();
			//my_player.ShowLyrics();
			//my_player.SaveConfig();
		}
		GetLocalTime(&current_time);
		if (current_time - temp_time > LYRIC_REFRESH && my_player.IsPlaying())		//�����ǰʱ����֮ǰ��ʱ������LYRIC_REFRESH���룬�������ڲ��ţ���ˢ��һ�θ��
		{
			temp_time = current_time;
			my_player.ShowLyrics();
		}
		if (my_player.SongIsOver())
		{
			if (!my_player.PlayTrack(NEXT))		//˳�򲥷�ģʽ���б��еĸ���������ϣ�PlayTrack�����᷵��false
				my_player.MusicControl(Command::STOP);		//ֹͣ����
		}
		if (_kbhit())
		{
			switch (GetKey())
			{
			//case 'P': my_player.MusicControl(Command::PLAY); break;
			case 'P': case SPACE_KEY: my_player.MusicControl(Command::PLAY_PAUSE); break;		//����/��ͣ
			case 'S': my_player.MusicControl(Command::STOP); break;		//ֹͣ
			case 'N': my_player.PlayTrack(NEXT); break;		//��һ��
			case 'V': my_player.PlayTrack(PREVIOUS); break;		//��һ��
			case RIGHT_KEY: my_player.MusicControl(Command::FF); break;		//���
			case LEFT_KEY:my_player.MusicControl(Command::REW); break;		//����
			case 'T': my_player.SetPath(); break;		//����·��
			case UP_KEY: my_player.MusicControl(Command::VOLUME_UP); break;		//������
			case DOWN_KEY:my_player.MusicControl(Command::VOLUME_DOWN); break;		//������
			case 'K': my_player.SetTrack(); break;		//����ָ������
			case '[': my_player.SwitchPlaylist(PREVIOUS); break;		//�����б���ǰ��ҳ
			case ']': my_player.SwitchPlaylist(NEXT); break;			//�����б����ҳ
			case 'M': my_player.SetRepeatMode(); break;			//�л�ѭ��ģʽ
			//case 'L': my_player.ConvertLyric(); break;
			case ESC_KEY:
				//my_player.GetConsoleSetting();
				my_player.SaveConfig();
				return 0;
			}
			my_player.ShowInfo();
			my_player.ShowProgressBar();
			my_player.ShowLyrics(true);
			my_player.ShowPlaylist();
		}

		width_t = GetWindowWidth();
		hight_t = GetWindowHight();
		if (width != width_t || hight != hight_t)		//�������̨���ڴ�С�����ı�
		{
			width = width_t;
			hight = hight_t;
			if (width_t >= MIN_WIDTH && hight_t >= MIN_HIGHT)		//ȷ���趨�Ĵ��ڴ�С����С����Сֵ
			{
				//���ϵͳ��windows10����ȸı�����½�����̨��������С����Ϊ���ڴ�С������ʹ����̨���ڴ�С�����󲻻���ʾ��������
				//��Windws10���µ�ϵͳ�޷�ͨ���ı䴰�ڴ�С���ı仺������С�������ᵼ�´��ڵ�С���޷��������Բ�Ӧ����
				//�ı䴰�ڴ�С��ʱ�����軺������С��
				//��VS2013û���ж�win10���ϵĺ�����������win8���ϴ��棬��������win7��
				if (IsWindows8OrGreater())
				{
					char buff[32];
					sprintf_s(buff, 31, "mode con:cols=%d lines=%d", width_t, hight_t);
					system(buff);		//���ô��ڵĿ�Ⱥ͸߶�
				}

				my_player.GetWindowsSize(width_t, hight_t);
				//����̨���ڴ�С�ı�ʱ����ˢ����Ϣ
				system("cls");
				my_player.ShowInfo();
				my_player.ShowProgressBar();
				my_player.ShowLyrics(true);
				my_player.ShowPlaylist();
				my_player.SaveConfig();
			}
			else
			{
				//windows10
				if (IsWindows8OrGreater())
				{
					char buff[32];
					sprintf_s(buff, 31, "mode con:cols=%d lines=%d", MIN_WIDTH, MIN_HIGHT);
					system(buff);		//���ô��ڵĿ�Ⱥ͸߶�
				}
			}
		}
		Sleep(20);			//����������ѭ��ִ�е�Ƶ�ʣ��Լ�СCPU������
	}
}