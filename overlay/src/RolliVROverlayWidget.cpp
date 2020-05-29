#include <QtCore/qmath.h>
#include "RolliVROverlayWidget.h"
#include "ui_RolliVROverlayWidget.h"

RolliVROverlayWidget::RolliVROverlayWidget(QWidget *parent) :
		QWidget(parent),
		m_ui(new Ui::RolliVROverlayWidget)
{
    m_ui->setupUi(this);
	m_ui->advancedConfigurationGroupBox->setVisible(false);

	m_currentHeightOffset = 0;
	m_currentXOffset = 0;
	m_currentYOffset = 0;
	m_currentRotationOffset = 0;
	m_currentTurnSpeed = 1;
	m_currentMovementSpeed = 1;
	m_started = false;

	updateHeightOffsetLabel();
	updateXOffsetLabel();
	updateYOffsetLabel();
	updateRotationOffsetLabel();
	updateTurnSpeedLabel();
	updateMovementSpeedLabel();
	emit ConfigurationChanged();
}

RolliVROverlayWidget::~RolliVROverlayWidget()
{
    delete m_ui;
}

/*void RolliVROverlayWidget::on_quitOverlayPushButton_clicked()
{
    QApplication::quit();
}*/

/*void RolliVROverlayWidget::on_resetPushButton_clicked()
{
	emit Reset();
}*/

void RolliVROverlayWidget::on_startStopPushButton_clicked()
{
	if (m_started) {
		emit Stop();
		m_ui->startInfoLabel->setVisible(true);
		m_ui->startStopPushButton->setText("START FORCED MOVEMENT");
		m_ui->advancedConfigurationGroupBox->setVisible(false);
	} else {
		emit Start();
		m_ui->startInfoLabel->setVisible(false);
		m_ui->startStopPushButton->setText("STOP FORCED MOVEMENT");
		m_ui->advancedConfigurationGroupBox->setVisible(true);
	}

	m_started = !m_started;
}

void RolliVROverlayWidget::MoveOffsets(float x, float y, float rotation)
{
	m_currentXOffset = x;
	m_currentYOffset = y;
	m_currentRotationOffset = qRadiansToDegrees(rotation);
	updateXOffsetLabel();
	updateYOffsetLabel();
	updateRotationOffsetLabel();
}

void RolliVROverlayWidget::updateHeightOffsetLabel()
{
	m_ui->heightOffsetLabel->setText(QString().setNum(m_currentHeightOffset, 'f', 2) + QString("m"));
}

void RolliVROverlayWidget::updateXOffsetLabel()
{
	m_ui->xOffsetLabel->setText(QString().setNum(m_currentXOffset, 'f', 2) + QString("m"));
}

void RolliVROverlayWidget::updateYOffsetLabel()
{
	m_ui->yOffsetLabel->setText(QString().setNum(m_currentYOffset, 'f', 2) + QString("m"));
}

void RolliVROverlayWidget::updateRotationOffsetLabel()
{
	m_ui->rotationOffsetLabel->setText(QString().setNum((int)m_currentRotationOffset) + QString("°"));
}

void RolliVROverlayWidget::updateTurnSpeedLabel()
{
	m_ui->turnSpeedLabel->setText(QString().setNum((int)(m_currentTurnSpeed * 100)) + QString("%"));
}

void RolliVROverlayWidget::updateMovementSpeedLabel()
{
	m_ui->movementSpeedLabel->setText(QString().setNum((int)(m_currentMovementSpeed * 100)) + QString("%"));
}

void RolliVROverlayWidget::on_decrementHeightOffsetPushButton_clicked()
{
	m_currentHeightOffset = qMax(m_currentHeightOffset - 0.1f, -1.0f);
	updateHeightOffsetLabel();
	emit ConfigurationChanged();
}

void RolliVROverlayWidget::on_incrementHeightOffsetPushButton_clicked()
{
	m_currentHeightOffset = qMin(m_currentHeightOffset + 0.1f, 2.0f);
	updateHeightOffsetLabel();
	emit ConfigurationChanged();
}

void RolliVROverlayWidget::on_decrementXOffsetPushButton_clicked()
{
	m_currentXOffset -= 0.1f;
	updateXOffsetLabel();
	emit ConfigurationChanged();
}

void RolliVROverlayWidget::on_incrementXOffsetPushButton_clicked()
{
	m_currentXOffset += 0.1f;
	updateXOffsetLabel();
	emit ConfigurationChanged();
}

void RolliVROverlayWidget::on_decrementYOffsetPushButton_clicked()
{
	m_currentYOffset -= 0.1f;
	updateYOffsetLabel();
	emit ConfigurationChanged();
}

void RolliVROverlayWidget::on_incrementYOffsetPushButton_clicked()
{
	m_currentYOffset += 0.1f;
	updateYOffsetLabel();
	emit ConfigurationChanged();
}

void RolliVROverlayWidget::on_decrementRotationOffsetPushButton_clicked()
{
	m_currentRotationOffset -= 5.0f;
	if (m_currentRotationOffset < 0.0f) {
		m_currentRotationOffset = 355.0f;
	}
	updateRotationOffsetLabel();
	emit ConfigurationChanged();
}

void RolliVROverlayWidget::on_incrementRotationOffsetPushButton_clicked()
{
	m_currentRotationOffset += 5.0f;
	if (m_currentRotationOffset >= 360.0f) {
		m_currentRotationOffset = 0.0f;
	}
	updateRotationOffsetLabel();
	emit ConfigurationChanged();
}

void RolliVROverlayWidget::on_decrementTurnSpeedPushButton_clicked()
{
	m_currentTurnSpeed = qMax(m_currentTurnSpeed - 0.1f, 0.0f);
	updateTurnSpeedLabel();
	emit ConfigurationChanged();
}

void RolliVROverlayWidget::on_incrementTurnSpeedPushButton_clicked()
{
	m_currentTurnSpeed = qMin(m_currentTurnSpeed + 0.1f, 2.0f);
	updateTurnSpeedLabel();
	emit ConfigurationChanged();
}

void RolliVROverlayWidget::on_decrementMovementSpeedPushButton_clicked()
{
	m_currentMovementSpeed = qMax(m_currentMovementSpeed - 0.1f, 0.0f);
	updateMovementSpeedLabel();
	emit ConfigurationChanged();
}

void RolliVROverlayWidget::on_incrementMovementSpeedPushButton_clicked()
{
	m_currentMovementSpeed = qMin(m_currentMovementSpeed + 0.1f, 2.0f);
	updateMovementSpeedLabel();
	emit ConfigurationChanged();
}

float RolliVROverlayWidget::GetHeightOffset() const
{
	return m_currentHeightOffset;
}

float RolliVROverlayWidget::GetXOffset() const
{
	return m_currentXOffset;
}

float RolliVROverlayWidget::GetYOffset() const
{
	return m_currentYOffset;
}

float RolliVROverlayWidget::GetRotationOffset() const
{
	return qDegreesToRadians(m_currentRotationOffset);
}

float RolliVROverlayWidget::GetTurnSpeed() const
{
	return m_currentTurnSpeed;
}

float RolliVROverlayWidget::GetMovementSpeed() const
{
	return m_currentMovementSpeed;
}